#include "Trainer.h"


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

bool Trainer::IdleWait(std::string_view searchmessage, std::string_view foundmessage)
{
	std::cout << searchmessage << "\n";
	for (;;) {
		procId = GetProcessID();
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
	std::vector<BYTE> tmp(instructions.size());
	for (int i = 0; i < instructions.size(); ++i) {
		ReadProcessMemory(hProcess, (BYTE*)startaddress, &tmp[i], sizeof(BYTE), nullptr);
		startaddress++;
	}
	stores[name] = { startaddress - (instructions.size()), tmp };
	WriteAddress(startaddress - (instructions.size()), instructions);
}

void Trainer::Restore(std::string name)
{
	if (stores[name].first == 0 || stores[name].second.size() == 0) return;
	WriteAddress(stores[name].first, stores[name].second);
}

void Trainer::Freeze()
{
	DebugActiveProcess(procId);
}

void Trainer::Unfreeze()
{
	DebugActiveProcessStop(procId);
}

DWORD Trainer::GetProcId()
{
	return procId;
}

HANDLE Trainer::GetProcHandle()
{
	return hProcess;
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
