#pragma once

#pragma warning(disable: 6387)
#pragma comment(lib, "urlmon.lib")
#pragma comment(lib, "winmm.lib")

#define log(x)\
std::wcout << x << "\n"

#define input(key)\
GetAsyncKeyState(key) & 0x8000

#define error(msg)\
MessageBoxA(NULL, msg, "ERROR", MB_ICONERROR);\
exit(-1)

#include <memory>
#include "Trainer.h"
#include "Ini.h"
#include "Dialog.h"

#define error(msg)\
MessageBoxA(NULL, msg, "ERROR", MB_ICONERROR);\
exit(-1)

using namespace mINI;

inline void fnFly(std::shared_ptr<Trainer> witness, bool active) {
	witness->Freeze();
	if (active) {
		{
			witness->Patch("XP1", 0x14023C058, { 0x90, 0x90, 0x90, 0x90, 0x90 });
			witness->Patch("XP2", 0x140186147, { 0x90, 0x90, 0x90, 0x90, 0x90 });
			witness->Patch("XP3", 0x140246EFC, { 0x90, 0x90, 0x90, 0x90, 0x90 });
			witness->Patch("XP4", 0x1401B4401, { 0x90, 0x90, 0x90, 0x90, 0x90 });
			witness->Patch("XP5", 0x14024162D, { 0x90, 0x90, 0x90, 0x90, 0x90 });
			witness->Patch("XP6", 0x14023FC59, { 0x90, 0x90, 0x90, 0x90 });
		}
		{
			witness->Patch("YP1", 0x14018614F, { 0x90, 0x90, 0x90 });
			witness->Patch("YP2", 0x1401C898B, { 0x90, 0x90, 0x90, 0x90, 0x90 });
			witness->Patch("YP3", 0x1401C9596, { 0x90, 0x90, 0x90, 0x90, 0x90 });
			witness->Patch("YP4", 0x140246F01, { 0x90, 0x90, 0x90 });
			witness->Patch("YP5", 0x14023C05D, { 0x90, 0x90, 0x90 });
			witness->Patch("YP6", 0x14023FC60, { 0x90, 0x90, 0x90 });
			witness->Patch("YP7", 0x140241628, { 0x90, 0x90, 0x90, 0x90, 0x90 });
			witness->Patch("YP8", 0x14023FC68, { 0x90, 0x90, 0x90, 0x90, 0x90 });
			witness->Patch("YP9", 0x1401B4443, { 0x90, 0x90, 0x90 });
			witness->Patch("YP10", 0x14023BE41, { 0x90, 0x90, 0x90, 0x90, 0x90, 0x90 });
			witness->Patch("YP11", 0x1401B4443, { 0x90, 0x90, 0x90 });

			//Camera
			witness->Patch("YP12", 0x140247701, { 0x90, 0x90, 0x90, 0x90, 0x90, 0x90 });
			witness->Patch("YP13", 0x1402470CD, { 0x90, 0x90, 0x90, 0x90, 0x90, 0x90 });
		}
		witness->Unfreeze();
		return;
	}
	for (int i = 1; i <= 6; ++i) {
		witness->Restore("XP" + std::to_string(i));
	}
	for (int i = 1; i <= 13; ++i) {
		witness->Restore("YP" + std::to_string(i));
	}
	witness->Unfreeze();
}

inline void fnFlyControls(std::shared_ptr<Trainer> witness, Dialog& dialog, INIStructure& ini) {
	while (true) {
		float pitch{}, yaw{}, speed{};
		bool state = dialog.GetEntry("gameChanger", "fly")->second;
		if ((input('W') || input('S') || input('A') || input('D')) && state) {
			pitch = witness->Read<float>("UpDownRotPitch");
			yaw = witness->Read<float>("LeftRightRotYaw");
			if (ini["movement"]["flySpeed"].empty()) {
				error("flySpeed no value!");
			}
			try {
				speed = std::stof(ini["movement"]["flySpeed"]);
			}
			catch (...) {
				error("flySpeed illegal value!");
			}
		}
		if (input('W') && state) {
			float yp = witness->Read<float>("YPos");
			witness->Write("YPos", float(yp + (sinf(pitch) * 0.01 * speed)));
			
			float ycp = witness->Read<float>("YCamPos");
			witness->Write("YCamPos", float(ycp + (sinf(pitch) * 0.01 * speed)));
			
			float xp = witness->Read<float>("XPos");
			witness->Write("XPos", float(xp + (sinf(yaw) * 0.01 * speed)));
			
			float zp = witness->Read<float>("ZPos");
			witness->Write("ZPos", float(zp + (cosf(yaw) * 0.01 * speed)));
		}
		if (input('S') && state) {
			float yp = witness->Read<float>("YPos");
			witness->Write("YPos", float(yp - (sinf(pitch) * 0.01 * speed)));
			
			float ycp = witness->Read<float>("YCamPos");
			witness->Write("YCamPos", float(ycp - (sinf(pitch) * 0.01 * speed)));
			
			float xp = witness->Read<float>("XPos");
			witness->Write("XPos", float(xp - (sinf(yaw) * 0.01 * speed)));
			
			float zp = witness->Read<float>("ZPos");
			witness->Write("ZPos", float(zp - (cosf(yaw) * 0.01 * speed)));
		}
		if (input('A') && state) {
			float xp = witness->Read<float>("XPos");
			witness->Write("XPos", float(xp + (sinf(yaw + float(M_PI) / 2) * 0.01 * speed)));
			
			float zp = witness->Read<float>("ZPos");
			witness->Write("ZPos", float(zp + (cosf(yaw + float(M_PI) / 2) * 0.01 * speed)));
		}
		if (input('D') && state) {
			float xp = witness->Read<float>("XPos");
			witness->Write("XPos", float(xp + (sinf(yaw - float(M_PI) / 2) * 0.01 * speed)));
			
			float zp = witness->Read<float>("ZPos");
			witness->Write("ZPos", float(zp + (cosf(yaw - float(M_PI) / 2) * 0.01 * speed)));
		}
		Sleep(1);
	}
}

inline void fnSprintControls(std::shared_ptr<Trainer> witness, Dialog& dialog, INIStructure& ini, int& sprintKey) {
	while (true) {
		if (input(sprintKey) && dialog.GetEntry("gameChanger", "fasterSprint")->second) {
			if (ini["movement"]["sprintSpeed"].empty()) {
				error("sprintSpeed no value!");
			}
			else {
				try {
					witness->Write<float>("Speed", std::stof(ini["movement"]["sprintSpeed"]));
				}
				catch (...) {
					error("sprintSpeed illegal value!");
				}
			}
		}
		Sleep(1);
	}
}

inline void fnRestoreAll(std::shared_ptr<Trainer> witness) {
	for (int i = 1; i <= 6; ++i) {
		witness->Restore("XP" + std::to_string(i));
	}
	for (int i = 1; i <= 11; ++i) {
		witness->Restore("YP" + std::to_string(i));
	}
	witness->Restore("MuteGame");
	witness->Restore("LeaveSolveEnviroment");
	witness->WriteAddress(0x1400BF552, { 0x88, 0x45, 0x0F, 0x84, 0xC0, 0x74, 0x6E });
	witness->WriteAddress(0x14022ECFA, { 0xE8, 0x91, 0xC1, 0xE8, 0xFF });
	witness->WriteAddress(0x140064C09, { 0xE8, 0x42, 0x17, 0x00, 0x00 });
	witness->Restore("NoNodLimit");
}

inline void fnStickToProcess(Dialog& dialog, bool& hide) {
	while (true) {
		if (dialog.GetEntry("misc", "stickToProcess")->second) {
			if (GetConsoleWindow() == GetForegroundWindow()) {
				SetForegroundWindow(FindWindowA(NULL, "The Witness"));
			}
			RECT r;
			HWND hwndWitness = FindWindowA(NULL, "The Witness");
			GetWindowRect(hwndWitness, &r);
			if (hwndWitness != GetForegroundWindow()) {
				ShowWindow(GetConsoleWindow(), SW_HIDE);
			}
			else if (!hide) {
				ShowWindow(GetConsoleWindow(), SW_RESTORE);
				SetWindowPos(GetConsoleWindow(), HWND_TOPMOST, r.left, r.top, 0, 0, SWP_NOSIZE);
			}
		}
		Sleep(1);
	}
}

inline void fnSprintKey(INIStructure& ini, int& sprintKey) {
	if (ini["misc"]["sprintKey"].empty()) {
		error("sprintKey no value!");
	}
	try {
		sprintKey = std::stoul(ini["misc"]["sprintKey"], nullptr, 16);
	}
	catch (...) {
		error("sprintKey illegal value!");
	}
}

inline void fnTeleport(std::shared_ptr<Trainer> witness, INIStructure& ini, float x, float y, float z) {
	if (ini["misc"]["teleportForceInterval"].empty()) {
		error("teleportForceInterval no value!");
	}
	else {
		try {
			for (int i = 0; i < std::stoi(ini["misc"]["teleportForceInterval"]); ++i) {
				witness->Write("XPos", x);
				witness->Write("YPos", y);
				witness->Write("ZPos", z);
				Sleep(100);
			}
		}
		catch (...) {
			error("teleportForceInterval illegal value!");
		}
	}
}

inline void fnRotation(std::shared_ptr<Trainer> witness, float pitch, float yaw) {
	witness->Write("UpDownRotPitch", pitch);
	witness->Write("LeftRightRotYaw", yaw);
}

inline void fnExportRes(int id, const char* type, const char* destination) {
	HRSRC myResource = FindResourceA(NULL, MAKEINTRESOURCE(id), type);
	if (myResource == NULL)
		return;
	DWORD myResourceSize = SizeofResource(NULL, myResource);
	HGLOBAL myResourceData = LoadResource(NULL, myResource);
	if (myResourceData == NULL)
		return;
	void* lpResLock = LockResource(myResourceData);
	if (lpResLock == NULL)
		return;
	FILE* fh;
	fopen_s(&fh, destination, "wb+");
	fwrite(lpResLock, myResourceSize, 1, fh);
	fclose(fh);
}