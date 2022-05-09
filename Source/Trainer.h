#pragma once

#include <iostream>
#include <string_view>
#include <windows.h>
#include <TlHelp32.h>
#include <vector>
#include <map>
#include <concepts>
#include <utility>


class Trainer {
	HANDLE hProcess;
	std::string_view procName;
	DWORD procId;
	uintptr_t modBase;
	std::map<std::string_view, uintptr_t> entrys;
	std::map<std::string_view, std::pair<uintptr_t, std::vector<BYTE>>> stores;

public:

	Trainer(std::string_view procName)
		: procName(procName), procId(GetProcessID()), modBase(GetModuleBaseAddress()) 
	{
		hProcess = OpenProcess(PROCESS_ALL_ACCESS, NULL, procId);
	}

	void AddEntry(std::string_view name, uintptr_t dynamicBaseOffset, const std::vector<unsigned int>& offsets, uintptr_t endoffset);

	bool IdleWait(std::string_view searchmessage,std::string_view foundmessage);

	template<typename Ret>
	Ret& Read(std::string_view name) {
		Ret value{};
		ReadProcessMemory(hProcess, (BYTE*)entrys[name], &value, sizeof(value), nullptr);
		return value;
	}

	template<typename Type>
	requires std::integral<Type> || std::floating_point<Type>
	void Write(std::string_view name, Type value) {
		WriteProcessMemory(hProcess, (BYTE*)entrys[name], &value, sizeof(value), nullptr);
	}

	template<typename Ret>
	Ret ReadAddress(uintptr_t startaddress) {
		Ret buf{};
		ReadProcessMemory(hProcess, (BYTE*)startaddress, &buf, sizeof(buf), nullptr);
		return buf;
	}

	void WriteAddress(uintptr_t startaddress, const std::vector<BYTE>& bytes);

	void Patch(std::string_view name, uintptr_t startaddress, const std::vector<BYTE>& instructions);

	void Restore(std::string name);

	void Freeze();

	void Unfreeze();

	DWORD GetProcId();

	HANDLE GetProcHandle();

private:
	DWORD GetProcessID();

	uintptr_t GetModuleBaseAddress();

};
