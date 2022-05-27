#include <iostream>
#define _USE_MATH_DEFINES
#include <math.h>
#include <memory>
#include <string>
#include <fcntl.h>
#include <io.h>
#include <fstream>
#include <algorithm>
#include "Functions.h"
#include "Trainer.h"
#include "Dialog.h"
#include "Ini.h"
#include "../resource.h"

#pragma comment(lib, "winmm.lib")
#define log(x)\
std::wcout << x << "\n"

#define input(key)\
GetAsyncKeyState(key) & 0x8000

#define error(msg)\
MessageBoxA(NULL, msg, "ERROR", MB_ICONERROR);\
exit(-1)

using namespace mINI;

int main() {
	HWND _console = GetConsoleWindow();

	RECT r;
	GetWindowRect(_console, &r);
	MoveWindow(_console, r.left, r.top, 617, 119, TRUE);
	SetWindowTextA(_console, "Searching for witness64_d3d11.exe .");
	SetWindowPos(_console, HWND_NOTOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
	SetLayeredWindowAttributes(_console, NULL, 255, LWA_ALPHA);
	ShowWindow(_console, SW_SHOW);

	std::cout << "To Navigate back to the menu, press backspace\nTo Hide/Show the window, press Numpad Asterisk\n";
	std::shared_ptr<Trainer> witness = std::make_shared<Trainer>("witness64_d3d11.exe");
	
	witness->IdleWait("You have to be ingame before you open the trainer!\nSearching for witness64_d3d11.exe ...", "Found witness64_d3d11.exe", [&]() {
		char* text = new char[MAX_PATH];
		int size = GetWindowTextA(_console, text, MAX_PATH);
		std::string str(text, size);
		SetWindowTextA(_console, (str + ".").c_str());
		delete[] text;
		if(std::count(str.begin(), str.end(), '.') >= 86) SetWindowTextA(_console, "Searching for witness64_d3d11.exe .");
	});
	witness->StartCheckThread();
	SetWindowTextA(_console, "-survivalizeed's-The-Witness-Trainer-");

	if (GetFileAttributes("C:\\Users\\Public\\Documents\\sTWTsettings.ini") == INVALID_FILE_ATTRIBUTES && GetLastError() == ERROR_FILE_NOT_FOUND) {
		INIFile file("C:\\Users\\Public\\Documents\\sTWTsettings.ini");
		INIStructure ini;
		ini["movement"]["flySpeed"] = "25";
		ini["movement"]["sprintSpeed"] = "20";
		ini["misc"]["playTuneOnStart"] = "0";
		ini["misc"]["alphaStickToProcess"] = "100";
		ini["misc"]["sprintKey"] = "0xA0";
		ini["misc"]["teleportForceInterval"] = "10";
		file.generate(ini);
	}
	INIFile file("C:\\Users\\Public\\Documents\\sTWTsettings.ini");
	INIStructure ini;
	file.read(ini);

	Dialog dialog(L"-survivalizeed's-The-Witness-Trainer-");
	dialog.Set("menu",	"gameChanger",	{ L"Numpad-0------------------GameChanger", false });
	dialog.Set("menu",	"fun",			{ L"Numpad-1--------------------------Fun", false });
	dialog.Set("menu",	"misc",			{ L"Numpad-2-------------------------Misc", false });
	dialog.Set("menu",	"teleports",	{ L"Numpad-3--------------------Teleports", false });
	dialog.Set("menu",	"tune",			{ L"Numpad-4-------------------------Tune", false });
	dialog.Set("menu",	"quit",			{ L"Numpad-5-------------------------Quit", false });

	dialog.Set("gameChanger",	"fly",					{ L"Numpad-0--------------------------Fly", false });
	dialog.Set("gameChanger",	"fasterSprint",			{ L"Numpad-1----------------Faster-Sprint", false });
	dialog.Set("gameChanger",	"allSolutionsWork",		{ L"Numpad-2-----------All-Solutions-Work", false });
	dialog.Set("gameChanger",	"leaveSolve",			{ L"Numpad-3------------------Leave-Solve", false });
	dialog.Set("gameChanger",	"leaveSolveEnviroment",	{ L"Numpad-4-------Leave-Solve-Enviroment", false });
	dialog.Set("gameChanger",	"savePosition",			{ L"Numpad-5----------------Save-Position", false });
	dialog.Set("gameChanger",	"moveToPosition",		{ L"Numpad-6-------------Move-To-Position", false });

	dialog.Set("fun", "noNodLimit", { L"Numpad-0-----------------No-Nod-Limit", false });

	dialog.Set("misc",	"disableSave",			{ L"Numpad-0-----------------Disable-Save", false });
	dialog.Set("misc",	"disableSaveNoMessage",	{ L"Numpad-1------Disable-Save-No-Message", false });
	dialog.Set("misc",	"openGameDirectory",	{ L"Numpad-2----------Open-Game-Directory", false });
	dialog.Set("misc",	"openSettings",			{ L"Numpad-3----------------Open-Settings", false });
	dialog.Set("misc",	"reloadSettings",		{ L"Numpad-4--------------Reload-Settings", false });
	dialog.Set("misc",	"muteGame",				{ L"Numpad-5--------------------Mute-Game", false });
	dialog.Set("misc",	"stickToProcess",		{ L"Numpad-6-------------Stick-To-Process", false });
	dialog.Set("misc",  "installHackedSave",	{ L"Numpad-7----------Install-Hacked-Save", false });

	dialog.Set("teleports", "tutorial",		{ L"Numpad-0---------------------Tutorial", false });
	dialog.Set("teleports", "turntable",	{ L"Numpad-1--------------------Turntable", false });
	dialog.Set("teleports", "top",			{ L"Numpad-2--------------------------Top", false });
	dialog.Set("teleports", "ruin",			{ L"Numpad-3-------------------------Ruin", false });
	dialog.Set("teleports", "end",			{ L"Numpad-4------------------------- End", false });

	dialog.PushDialog(dialog.GetDialog("menu"));

	waveOutSetVolume(NULL, 0xAAAAAAAA);
	if (ini["misc"]["playTuneOnStart"] != "0") {
		PlaySound(MAKEINTRESOURCE(101), GetModuleHandle(NULL), SND_RESOURCE | SND_LOOP | SND_ASYNC);
		dialog.Set("menu", "tune", { L"", true });
	}

	witness->AddEntry("XPos", 0x0062D0A8, { 0x148, 0x970, 0x228, 0x10, 0x50, 0x20, 0x30 }, 0x0);
	witness->AddEntry("YPos", 0x0062D0A8, { 0x148, 0x970, 0x228, 0x10, 0x50, 0x20, 0x30 }, 0x4);
	witness->AddEntry("ZPos", 0x0062D0A8, { 0x148, 0x970, 0x228, 0x10, 0x50, 0x20, 0x30 }, -0x4);
	witness->AddEntry("Speed", 0x0062D0A8, { 0x148, 0x970, 0x228, 0x10, 0x50, 0x20, 0x30 }, 0x10C);
	witness->AddEntry("UpDownRotPitch", 0x006303C0, {}, 0);
	witness->AddEntry("LeftRightRotYaw", 0x006303BC, {}, 0);
	
	bool hide = false;

	float x, y, z;
	x = y = z = 0.f;

	int sprintKey{};

	fnSprintKey(ini, sprintKey);

	POINT windowPos{};

	while (witness->StillValid()) {		
		if (!hide) {
			if (input(VK_BACK)) {
				dialog.PopDialog();
				Sleep(200);
			}
			if (input(VK_NUMPAD0)) {
				if (dialog.GetDialog("menu") == dialog.GetCurrentDialog()) {
					dialog.PushDialog(dialog.GetDialog("gameChanger"));
					Sleep(200);
				}
				else if (dialog.GetDialog("gameChanger") == dialog.GetCurrentDialog()) {
					dialog.InvertEntry("gameChanger", "fly");
					fnFly(witness, dialog.GetEntry("gameChanger", "fly")->second);
					Sleep(200);
				}
				else if (dialog.GetDialog("fun") == dialog.GetCurrentDialog()) {
					dialog.InvertEntry("fun", "noNodLimit");
					if (dialog.GetEntry("fun", "noNodLimit")->second) 
						witness->Patch("NoNodLimit", 0x14023CCA2, {0x90,0x90,0x90,0x90});
					else 
						witness->Restore("NoNodLimit");
					Sleep(200);
				}
				else if (dialog.GetDialog("misc") == dialog.GetCurrentDialog()) {
					dialog.InvertEntry("misc", "disableSave");
					if (dialog.GetEntry("misc", "disableSave")->second) 
						witness->Patch("DisableSave", 0x140064C09, { 0x90, 0x90, 0x90, 0x90, 0x90 });
					else {
						witness->WriteAddress(0x140064C09, { 0xE8, 0x42, 0x17, 0x00, 0x00 });
						dialog.Set("misc", "disableSaveNoMessage", { L"", false });
					}
					Sleep(200);
				}
				else if (dialog.GetDialog("teleports") == dialog.GetCurrentDialog()) {
					fnRotation(witness, 0.0653167f, 2.88611f);
					fnTeleport(witness, ini, -164.53f, 5.74332f, -133.377f);
					Sleep(200);
				}
			}
			if (input(VK_NUMPAD1)) {
				if (dialog.GetDialog("menu") == dialog.GetCurrentDialog()) {
					dialog.PushDialog(dialog.GetDialog("fun"));
					Sleep(200);
				}
				else if (dialog.GetDialog("gameChanger") == dialog.GetCurrentDialog()) {
					dialog.InvertEntry("gameChanger", "fasterSprint");
					Sleep(200);
				}
				else if (dialog.GetDialog("misc") == dialog.GetCurrentDialog()) {
					dialog.InvertEntry("misc", "disableSaveNoMessage");
					if (dialog.GetEntry("misc", "disableSaveNoMessage")->second) 
						witness->Patch("DisableSaveNoMessage", 0x140064C09, {0xB8, 0x01, 0x00, 0x00, 0x00});
					else {
						witness->WriteAddress(0x140064C09, { 0xE8, 0x42, 0x17, 0x00, 0x00 });
						dialog.Set("misc", "disableSave", { L"", false });
					}
					Sleep(200);
				}
				else if (dialog.GetDialog("teleports") == dialog.GetCurrentDialog()) {
					fnRotation(witness, -0.402977f, -0.0448767f);
					fnTeleport(witness, ini, -31.3635f, -11.7304f, -38.6826f);
					Sleep(200);
				}

			}
			if (input(VK_NUMPAD2)) {
				if (dialog.GetDialog("menu") == dialog.GetCurrentDialog()) {
					dialog.PushDialog(dialog.GetDialog("misc"));
					Sleep(200);
				}
				else if (dialog.GetDialog("gameChanger") == dialog.GetCurrentDialog()) {
					dialog.InvertEntry("gameChanger", "allSolutionsWork");
					if (dialog.GetEntry("gameChanger", "allSolutionsWork")->second)
						witness->WriteAddress(0x1400BF552, {0xC6, 0x45, 0x0F, 0x01, 0xB0, 0x01, 0x90});
					else {
						witness->WriteAddress(0x1400BF552, { 0x88, 0x45, 0x0F, 0x84, 0xC0, 0x74, 0x6E });
						witness->WriteAddress(0x14022ECFA, { 0xE8, 0x91, 0xC1, 0xE8, 0xFF });
						dialog.Set("gameChanger", "leaveSolve", { L"", false });
					}
					Sleep(200);
				}
				else if (dialog.GetDialog("misc") == dialog.GetCurrentDialog()) {
					DWORD size = MAX_PATH;
					char* filename = new char[MAX_PATH];
					QueryFullProcessImageNameA(witness->GetProcHandle(), 0, filename, &size);
					std::thread t1(system, (("explorer " + std::string(filename)).substr(0, ("explorer " + std::string(filename)).find_last_of("\\/"))).c_str());
					t1.detach();
					Sleep(200);
				}
				else if (dialog.GetDialog("teleports") == dialog.GetCurrentDialog()) {
					fnRotation(witness, -0.182666f, 2.82946f);
					fnTeleport(witness, ini, -51.6206f, 66.8419f, 144.698f);
				}
			}
			if (input(VK_NUMPAD3)) {
				if (dialog.GetDialog("menu") == dialog.GetCurrentDialog()) {
					dialog.PushDialog(dialog.GetDialog("teleports"));
					Sleep(200);
				}
				else if (dialog.GetDialog("gameChanger") == dialog.GetCurrentDialog()) {
					dialog.InvertEntry("gameChanger", "leaveSolve");
					if (dialog.GetEntry("gameChanger", "leaveSolve")->second) {
						witness->WriteAddress(0x1400BF552, { 0xC6, 0x45, 0x0F, 0x01, 0xB0, 0x01, 0x90 });
						witness->WriteAddress(0x14022ECFA, { 0xE8, 0x31, 0x06, 0xE9, 0xFF });
					}
					else {
						witness->WriteAddress(0x1400BF552, { 0x88, 0x45, 0x0F, 0x84, 0xC0, 0x74, 0x6E });
						witness->WriteAddress(0x14022ECFA, { 0xE8, 0x91, 0xC1, 0xE8, 0xFF });
						dialog.Set("gameChanger", "allSolutionsWork", { L"", false });
					}
					Sleep(200);
				}
				else if (dialog.GetDialog("misc") == dialog.GetCurrentDialog()) {
					std::thread t1(system, "notepad C:\\Users\\Public\\Documents\\sTWTsettings.ini");
					t1.detach();
					Sleep(200);
				}
				else if (dialog.GetDialog("teleports") == dialog.GetCurrentDialog()) {
					fnRotation(witness, -0.334823f, -1.75872f);
					fnTeleport(witness, ini, 135.093f, 39.3168f, 54.3465f);
				}
			}
			if (input(VK_NUMPAD4)) {
				if (dialog.GetDialog("menu") == dialog.GetCurrentDialog()) {
					if (dialog.GetEntry("menu", "tune")->second) 
						PlaySound(NULL, NULL, SND_ASYNC);
					else 
						PlaySound(MAKEINTRESOURCE(101), GetModuleHandle(NULL), SND_RESOURCE | SND_LOOP | SND_ASYNC);
					dialog.InvertEntry("menu", "tune");
					Sleep(200);
				}
				else if (dialog.GetDialog("gameChanger") == dialog.GetCurrentDialog()) {
					dialog.InvertEntry("gameChanger", "leaveSolveEnviroment");
					if (dialog.GetEntry("gameChanger", "leaveSolveEnviroment")->second)
						witness->Patch("LeaveSolveEnviroment", 0x14022DCFF, { 0xC7, 0x87, 0xB8, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x41, 0xB4, 0x01 });
					else 
						witness->Restore("LeaveSolveEnviroment");
					Sleep(200);
				}
				else if (dialog.GetDialog("misc") == dialog.GetCurrentDialog()) {
					file.read(ini);
					fnSprintKey(ini, sprintKey);
					Sleep(200);
				}
				else if (dialog.GetDialog("teleports") == dialog.GetCurrentDialog()) {
					fnRotation(witness, -0.0136076f, -3.01675f);
					fnTeleport(witness, ini, -49.1121f, - 0.0246615f, 206.573f);
				}
			}
			if (input(VK_NUMPAD5)) {
				if (dialog.GetDialog("menu") == dialog.GetCurrentDialog()) {
					fnRestoreAll(witness);
					CloseWindow(_console);
					return 0;
				}
				else if (dialog.GetDialog("gameChanger") == dialog.GetCurrentDialog()) {
					x = witness->Read<float>("XPos");
					y = witness->Read<float>("YPos");
					z = witness->Read<float>("ZPos");
					Sleep(200);
				}
				else if (dialog.GetDialog("misc") == dialog.GetCurrentDialog()) {
					dialog.InvertEntry("misc", "muteGame");
					if (dialog.GetEntry("misc", "muteGame")->second)
						witness->Patch("MuteGame", 0x1402A94B0, {0xC3, 0x90, 0x90});
					else
						witness->Restore("MuteGame");
					Sleep(200);
				}
			}
			if (input(VK_NUMPAD6)) {
				if (dialog.GetDialog("gameChanger") == dialog.GetCurrentDialog()) {
					if (x != 0 && y != 0 && z != 0) {
						fnTeleport(witness, ini, x, y, z);
					}
					Sleep(200);
				}
				else if (dialog.GetDialog("misc") == dialog.GetCurrentDialog()) {
					dialog.compactMode = !dialog.compactMode;
					dialog.InvertEntry("misc", "stickToProcess");
					if (dialog.GetEntry("misc", "stickToProcess")->second) {
						RECT r;
						GetWindowRect(_console, &r);
						windowPos.x = r.left;
						windowPos.y = r.top;
						SetWindowTextA(_console, "");
						if (ini["misc"]["alphaStickToProcess"].empty()) {
							error("alphaSticktoProcess no value!");
						}
						try {
							SetLayeredWindowAttributes(_console, NULL, std::stoi(ini["misc"]["alphaStickToProcess"]), LWA_ALPHA);
							std::thread t1(fnStickToProcess, std::ref(dialog.GetEntry("misc", "stickToProcess")->second), std::ref(hide));
							t1.detach();
						}
						catch (...) {
							error("alphaStickToProcess illegal value!");
						}
					}
					else {
						Sleep(100);
						SetWindowTextA(_console, "-survivalizeed's-The-Witness-Trainer-");
						SetWindowPos(_console, HWND_NOTOPMOST, windowPos.x, windowPos.y, 0, 0, SWP_NOSIZE);
						SetLayeredWindowAttributes(_console, NULL, 255, LWA_ALPHA);
						ShowWindow(_console, SW_SHOW);
					}
					Sleep(200);
				}
			}
			if (input(VK_NUMPAD7)) {
				if (dialog.GetDialog("misc") == dialog.GetCurrentDialog()) {
					char username[256 + 1];
					DWORD username_len = 256 + 1;
					GetUserNameA(username, &username_len);
					fnExportRes(IDR_WCS1, "WCS", 
						std::string("C:\\Users\\" + std::string(username) + "\\AppData\\Roaming\\The Witness\\TrainerSaveGame.witness_campaign").c_str());
					fnExportRes(IDB_PNG1, "PNG",
						std::string("C:\\Users\\" + std::string(username) + "\\AppData\\Roaming\\The Witness\\TrainerSaveGame.png").c_str());
					Sleep(200);
				}
			}
		}
		if (input(VK_MULTIPLY)) {
			hide = !hide;
			if (hide)
				ShowWindow(_console, SW_HIDE);
			else
				ShowWindow(_console, SW_SHOW);
			Sleep(200);
		}
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
		if (input('W') && dialog.GetEntry("gameChanger", "fly")->second) {
			float pitch = witness->Read<float>("UpDownRotPitch");
			float yaw = witness->Read<float>("LeftRightRotYaw");
			
			if (ini["movement"]["flySpeed"].empty()) {
				error("flySpeed no value!");
			}
			else {
				try {
					float speed = std::stof(ini["movement"]["flySpeed"]);
					float yp = witness->Read<float>("YPos");
					witness->Write("YPos", float(yp + (sinf(pitch) * 0.0001 * speed)));
					float xp = witness->Read<float>("XPos");
					witness->Write("XPos", float(xp + (sinf(yaw) * 0.0001 * speed)));
					float zp = witness->Read<float>("ZPos");
					witness->Write("ZPos", float(zp + (cosf(yaw) * 0.0001 * speed)));
				}
				catch (...) {
					error("flySpeed illegal value!");
				}
			}
		}
		if (input(VK_NUMPAD9)) {
			std::wcout << witness->Read<float>("XPos") << " " << witness->Read<float>("YPos") << " " << witness->Read<float>("ZPos") << "\n";
			std::wcout << witness->Read<float>("UpDownRotPitch") << " " << witness->Read<float>("LeftRightRotYaw");
			Sleep(200);
		}
	}
	system("CLS");
	log("Program ended...");
}