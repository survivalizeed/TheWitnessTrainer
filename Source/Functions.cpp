#include "Functions.h"

using namespace mINI;

void fnRemAutoPosition(std::shared_ptr<Trainer> witness, bool active)
{
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

void fnFlyControls(std::shared_ptr<Trainer> witness, Dialog& dialog, INIStructure& ini, bool& run)
{
	while (run) {
		float pitch{}, yaw{}, speed{};
		bool state = dialog.GetEntry("gameChanger", "fly")->second;
		if ((input('W') || input('S') || input('A') || input('D') || input('E') || input('Q')) && state) {
			pitch = witness->Read<float>("UpDownRotPitch");
			yaw = witness->Read<float>("LeftRightRotYaw");
			if (ini["movement"]["flySpeed"].empty()) {
				error("flySpeed no value!", witness);
			}
			try {
				speed = std::stof(ini["movement"]["flySpeed"]);
			}
			catch (...) {
				error("flySpeed illegal value!", witness);
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
		if (input('Q') && state) {
			float yp = witness->Read<float>("YPos");
			witness->Write("YPos", float(yp - 0.01 * speed));

			float ycp = witness->Read<float>("YCamPos");
			witness->Write("YCamPos", float(ycp - 0.01 * speed));
		}
		if (input('E') && state) {
			float yp = witness->Read<float>("YPos");
			witness->Write("YPos", float(yp + 0.01 * speed));

			float ycp = witness->Read<float>("YCamPos");
			witness->Write("YCamPos", float(ycp + 0.01 * speed));
		}
		Sleep(1);
	}
}

void fnSprintControls(std::shared_ptr<Trainer> witness, Dialog& dialog, INIStructure& ini, int& sprintKey, bool& run)
{
	while (run) {
		if (input(sprintKey) && dialog.GetEntry("gameChanger", "fasterSprint")->second) {
			if (ini["movement"]["sprintSpeed"].empty()) {
				error("sprintSpeed no value!", witness);
			}
			else {
				try {
					witness->Write<float>("Speed", std::stof(ini["movement"]["sprintSpeed"]));
				}
				catch (...) {
					error("sprintSpeed illegal value!", witness);
				}
			}
		}
		Sleep(1);
	}
}

void fnRestoreAll(std::shared_ptr<Trainer> witness)
{
	for (int i = 1; i <= 6; ++i) {
		witness->Restore("XP" + std::to_string(i));
	}
	for (int i = 1; i <= 13; ++i) {
		witness->Restore("YP" + std::to_string(i));
	}
	witness->Restore("MuteGame");
	witness->Restore("LeaveSolveEnviroment");
	witness->WriteAddress(0x1400BF552, { 0x88, 0x45, 0x0F, 0x84, 0xC0, 0x74, 0x6E });
	witness->WriteAddress(0x14022ECFA, { 0xE8, 0x91, 0xC1, 0xE8, 0xFF });
	witness->WriteAddress(0x140064C09, { 0xE8, 0x42, 0x17, 0x00, 0x00 });
	witness->Restore("NoNodLimit");
}

void fnStickToProcess(Dialog& dialog, bool& hide, bool& run)
{
	while (run) {
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

void fnSprintKey(std::shared_ptr<Trainer> witness, INIStructure& ini, int& sprintKey)
{
	if (ini["misc"]["sprintKey"].empty()) {
		error("sprintKey no value!", witness);
	}
	try {
		sprintKey = std::stoul(ini["misc"]["sprintKey"], nullptr, 16);
	}
	catch (...) {
		error("sprintKey illegal value!", witness);
	}
}

void fnTeleport(std::shared_ptr<Trainer> witness, Dialog& dialog, mINI::INIStructure& ini, float x, float y, float z, float pitch, float yaw)
{
	if (ini["misc"]["teleportForceInterval"].empty()) {
		error("teleportForceInterval no value!", witness);
	}
	else {
		try {
			Animation anim(witness);
			anim.Add(AnimationNode({ witness->Read<float>("XPos"), witness->Read<float>("YPos"), witness->Read<float>("ZPos") },
				{ 0.01f, 0.01f, 0.01f },
				Animation::WitRadToDegH(witness->Read<float>("LeftRightRotYaw")),
				Animation::WitRadToDegV(witness->Read<float>("UpDownRotPitch")), 0.01f, 0.01f));
			anim.Add(AnimationNode({ x,y,z }, { 0.f,0.f,0.f }, Animation::WitRadToDegH(yaw), Animation::WitRadToDegV(pitch), 0.f, 0.f));
			anim.StartAnimation(dialog);
			for (int i = 0; i < std::stoi(ini["misc"]["teleportForceInterval"]); ++i) {
				witness->Write("XPos", x);
				witness->Write("YPos", y);
				witness->Write("YCamPos", y + 1.69f);
				witness->Write("ZPos", z);
				witness->Write("UpDownRotPitch", pitch);
				witness->Write("LeftRightRotYaw", yaw);
				Sleep(100);
			}
		}
		catch (...) {
			error("teleportForceInterval illegal value!", witness);
		}
	}
}

void fnExportRes(int id, const char* type, const char* destination)
{
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

void fnChangeSavegamePath(std::shared_ptr<Trainer> witness, bool revert)
{
	if (revert) {
		witness->DiskPatch(0x510AAB, { 0x90,0x90,0x90,0x90,0x90,0x90,0x90,0x90,0x90, 0x90 });
		return;
	}
	system("CLS");
	std::wstring path;
	std::wcout << "New path: ";
	std::wcin >> path;
	std::vector<BYTE> hexAscii;
	for (int i = 0; i < path.size(); ++i) {
		std::stringstream ss;
		ss << std::hex << (int)path[i];
		int tmp;
		ss >> tmp;
		hexAscii.push_back((BYTE)tmp);
	}
	hexAscii.push_back(0x0);
	witness->DiskPatch(0x510A2F, hexAscii);		// Insert the given string into the executable
	witness->DiskPatch(0x6707B,					// Insert jump to a code-cave
		{ 0xE9, 0x28, 0x9A, 0x4A, 0x00, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90 });
	witness->DiskPatch(0x510AA8, 
		{ 
			0x48, 0x89, 0xC3, 0x48, 0xB8, 0x2F, 0x16, 0x51, 0x40, 0x01, 0x00, 0x00, 0x00,
			0x48, 0x89, 0x05, 0xBC, 0xC0, 0x11, 0x00, 0x4C, 0x89, 0xE9, 0x48, 0x8D, 0x15,
			0xBA, 0x2D, 0x00, 0x00, 0xE9, 0xB5, 0x65, 0xB5, 0xFF
		});
	
}
