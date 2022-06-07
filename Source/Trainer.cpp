#include "Trainer.h"


void Trainer::StartCheckThread()
{
	auto checkValidation = [&]() {
		for (;;) {
			if (GetProcessID() == 0) procValid = false;
			else procValid = true;
			if (killThread) return;
		}
	};
	std::thread async(checkValidation);
	async.detach();
}

void Trainer::AddEntry(std::string_view name, uintptr_t dynamicBaseOffset, const std::vector<unsigned int>& offsets, uintptr_t endoffset)
{
	uintptr_t addr = modBase + dynamicBaseOffset;
	for (unsigned int i = 0; i < offsets.size(); ++i)
	{
		ReadProcessMemory(hProcess, (BYTE*)addr, &addr, sizeof(addr), nullptr);
		addr += offsets[i];
	}
	entrys[name] = addr + endoffset;
}

void Trainer::AddStaticEntry(std::string_view name, uintptr_t staticAddress)
{
	entrys[name] = staticAddress;
}

bool Trainer::IdleWait(std::string_view searchmessage, std::string_view foundmessage, std::function<void()> callback)
{
	std::cout << searchmessage << "\n";
	for (;;) {
		procId = GetProcessID();
		callback();
		if (procId != 0) {
			std::cout << foundmessage << "\n";
			hProcess = OpenProcess(PROCESS_ALL_ACCESS, NULL, procId);
			modBase = GetModuleBaseAddress();
			return true;
		}
		Sleep(1);
	}
}

void Trainer::WriteAddress(uintptr_t startaddress, const std::vector<BYTE>& bytes)
{
	for (auto& iter : bytes) {
		WriteProcessMemory(hProcess, (BYTE*)startaddress, &iter, sizeof(BYTE), nullptr);
		startaddress++;
	}
}

void Trainer::Patch(std::string_view name, uintptr_t startaddress, const std::vector<BYTE>& instructions)
{
	int alreadyPatched = false;
	std::vector<BYTE> tmp(instructions.size());
	for (int i = 0; i < instructions.size(); ++i) {
		ReadProcessMemory(hProcess, (BYTE*)startaddress, &tmp[i], sizeof(BYTE), nullptr);
		if (tmp[i] == instructions[i])
			alreadyPatched++;
		startaddress++;
	}
	if (alreadyPatched == instructions.size()) return;
	stores[name] = { startaddress - (instructions.size()), tmp };
	WriteAddress(startaddress - (instructions.size()), instructions);
}

void Trainer::Restore(std::string_view name)
{
	if (stores.find(name) == stores.end()) 
		return;
	WriteAddress(stores[name].first, stores[name].second);
}

void Trainer::DiskPatch(uintptr_t rawAddress, std::vector<BYTE> instructions)
{
	TerminateProcess(GetProcHandle(), 0);
	while (StillValid()) Sleep(1);
	DWORD dwWritten = 0;
	HANDLE hFile = INVALID_HANDLE_VALUE;
	hFile = CreateFile(GetProcPath().c_str(), GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	SetFilePointer(hFile, rawAddress, 0, FILE_BEGIN);
	WriteFile(hFile, instructions.data(), instructions.size(), &dwWritten, NULL);
	CloseHandle(hFile);
}

void Trainer::Freeze()
{
	DebugActiveProcess(procId);
}

void Trainer::Unfreeze()
{
	DebugActiveProcessStop(procId);
}

bool Trainer::Reload()
{
	procId = GetProcessID();
	modBase = GetModuleBaseAddress();
	hProcess = OpenProcess(PROCESS_ALL_ACCESS, NULL, procId);
	return procId == 0 ? false : true;
}

bool Trainer::StillValid()
{
	return procValid;
}

DWORD Trainer::GetProcId()
{
	return procId;
}

HANDLE Trainer::GetProcHandle()
{
	return hProcess;
}

std::string Trainer::GetProcPath()
{
	return procPath;
}

Trainer::~Trainer()
{
	killThread = true;
}

DWORD Trainer::GetProcessID()
{
	wchar_t wBuf[100];
	mbstowcs(wBuf, procName.data(), 100);
	DWORD procId = 0;
	HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (hSnap != INVALID_HANDLE_VALUE)
	{
		PROCESSENTRY32 procEntry{};
		procEntry.dwSize = sizeof(procEntry);
		if (Process32First(hSnap, &procEntry))
		{
			do
			{
				wchar_t procEn[100];
				mbstowcs(procEn, procEntry.szExeFile, 100);
				if (!_wcsicmp(procEn, wBuf))
				{
					procId = procEntry.th32ProcessID;
					break;
				}
			} while (Process32Next(hSnap, &procEntry));

		}
	}
	CloseHandle(hSnap);
	return procId;
}

uintptr_t Trainer::GetModuleBaseAddress()
{
	wchar_t wBuf[100];
	mbstowcs(wBuf, procName.data(), 100);
	uintptr_t modBaseAddr = 0;
	HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, procId);
	if (hSnap != INVALID_HANDLE_VALUE)
	{
		MODULEENTRY32 modEntry{};
		modEntry.dwSize = sizeof(modEntry);
		if (Module32First(hSnap, &modEntry))
		{
			do
			{
				wchar_t modEn[100];
				mbstowcs(modEn, modEntry.szModule, 100);
				if (!_wcsicmp(modEn, wBuf))
				{
					modBaseAddr = (uintptr_t)modEntry.modBaseAddr;
					break;
				}
			} while (Module32Next(hSnap, &modEntry));
		}
	}
	CloseHandle(hSnap);
	return modBaseAddr;
}
