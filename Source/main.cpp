#include <iostream>
#define _USE_MATH_DEFINES
#include <math.h>
#include <memory>
#include <string>
#include <fcntl.h>
#include <io.h>
#include <fstream>
#include <algorithm>
#include "Trainer.h"
#include "SimpleConfigReader.h"
#include "../resource.h"

#pragma comment(lib, "winmm.lib")
#define log(x)\
std::cout << x << "\n"
#define input(key)\
GetAsyncKeyState(key) & 0x8000

bool lightDialog = false;

void fnDialog(const std::vector<std::pair<std::wstring, bool>>& entrys) {
	system("CLS");
	static_cast<void>(_setmode(_fileno(stdout), _O_U16TEXT));
	if (lightDialog) {
		RECT r;
		GetWindowRect(GetConsoleWindow(), &r);
		MoveWindow(GetConsoleWindow(), r.left, r.top, 329, 39 + 16 * static_cast<int>(entrys.size()), TRUE);
		std::wstring buf;
		for (auto& iter : entrys) {
			buf += iter.first;
			if (iter.second)
				buf += L"   \u2588\u2588\u2588";
			buf += L'\n';
		}
		buf.erase(buf.size() - 1);
		std::wcout << buf;
		return;
	}
	RECT r;
	GetWindowRect(GetConsoleWindow(), &r);
	MoveWindow(GetConsoleWindow(), r.left, r.top, 617, 119 + 16 * static_cast<int>(entrys.size()), TRUE);
	std::wstring begin = L"\u2591\u2591\u2592\u2592\u2593\u2588\u2588\u2588\u2588\u2588";
	std::wstring end = L"\u2588\u2588\u2588\u2588\u2588\u2593\u2592\u2592\u2591\u2591";
	std::wstring buf;
	buf += L"        " + begin;
	for (int i = 0; i < 36; ++i) buf += L"\u2588";
	buf += end + L"\n";
	buf += L"    " + begin;
	for (int i = 0; i < 44; ++i) buf += L"\u2588";
	buf += end + L"\n";
	buf += begin + L"-\u058D\u058D\u058D\u058D\u058D\u058D\u058D-survivalizeed's-The-Witness-Trainer-\u058D\u058D\u058D\u058D\u058D\u058D\u058D-" + end + L"\n";
	for (auto& iter : entrys) {
		std::wstring tmp = iter.first;
		if (iter.second) {
			tmp.insert(0, L"\u2588\u2588\u2593\u2593\u2592\u2591     ");
			tmp.insert(tmp.size(), L"     \u2591\u2592\u2593\u2593\u2588\u2588");
		} 
		else {
			tmp.insert(0, L"           ");
			tmp.insert(tmp.size(), L"           ");
		}
		buf += begin + tmp + end + L"\n";
	}
	buf += L"    " + begin;
	for (int i = 0; i < 44; ++i) buf += L"\u2588";
	buf += end + L"\n";
	buf += L"        " + begin;
	for (int i = 0; i < 36; ++i) buf += L"\u2588";
	buf += end;
	std::wcout << buf;
}

void fnFly(std::shared_ptr<Trainer> witness, bool active) {
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
		}
		return;
	}
	for (int i = 1; i <= 6; ++i) {
		witness->Restore("XP" + std::to_string(i));
	}
	for (int i = 1; i <= 11; ++i) {
		witness->Restore("YP" + std::to_string(i));
	}
}

void fnRestoreAll(std::shared_ptr<Trainer> witness) {
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

void fnStickToProcess(bool& state, bool& hide) {
	while (state) {
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
		Sleep(1);
	}
}

int main() {
	RECT r;
	GetWindowRect(GetConsoleWindow(), &r);
	MoveWindow(GetConsoleWindow(), r.left, r.top, 617, 119, TRUE);
	SetWindowTextA(GetConsoleWindow(), "Searching for witness64_d3d11.exe .");
	SetWindowPos(GetConsoleWindow(), HWND_NOTOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
	SetLayeredWindowAttributes(GetConsoleWindow(), NULL, 255, LWA_ALPHA);
	ShowWindow(GetConsoleWindow(), SW_SHOW);
	std::cout << "To Navigate back to the menu, press backspace\nTo Hide/Show the window, press Numpad Asterisk\n";
	std::shared_ptr<Trainer> witness = std::make_shared<Trainer>("witness64_d3d11.exe");
	witness->IdleWait("You have to be ingame before you open the trainer!\nSearching for witness64_d3d11.exe ...", "Found witness64_d3d11.exe", []() {
		char* text = new char[MAX_PATH];
		int size = GetWindowTextA(GetConsoleWindow(), text, MAX_PATH);
		std::string str(text, size);
		SetWindowTextA(GetConsoleWindow(), (str + ".").c_str());
		delete[] text;
		if(std::count(str.begin(), str.end(), '.') >= 86) SetWindowTextA(GetConsoleWindow(), "Searching for witness64_d3d11.exe .");
	});
	witness->StartCheckThread();
	SetWindowTextA(GetConsoleWindow(), "-survivalizeed's-The-Witness-Trainer-");

	std::ifstream checkEmpty("C:\\Users\\Public\\Documents\\sTWTsettings.conf");
	std::ofstream settings;
	if (!checkEmpty.good()) {
		settings.open("C:\\Users\\Public\\Documents\\sTWTsettings.conf", std::ios::out);
		settings << "FlySpeed=25;\nSprintSpeed=25;\nPlayTune=1;\nAlphaStickToProcess=100;";
		settings.close();
	}
	checkEmpty.close();
	SCR reader("C:\\Users\\Public\\Documents\\sTWTsettings.conf");


	std::vector<std::pair<std::wstring, bool>> menu = 
	{{L"Numpad-0------------GameChanger", false},
	{L"Numpad-1--------------------Fun", false},
	{L"Numpad-2-------------------Misc", false},
	{L"Numpad-3-------------------Tune", false},
	{L"Numpad-4-------------------Quit", false}};
	
	std::vector<std::pair<std::wstring, bool>> gamechanger =
	{{L"Numpad-0--------------------Fly", false},
	{L"Numpad-1-----------FasterSprint", false },
	{L"Numpad-2-------AllSolutionsWork", false },
	{L"Numpad-3-------------LeaveSolve", false},
	{L"Numpad-4---LeaveSolveEnviroment", false},
	{L"Numpad-5-----------SavePosition", false},
	{L"Numpad-6---------MoveToPosition", false} };

	std::vector<std::pair<std::wstring, bool>> fun =
	{{L"Numpad-0-------------NoNodLimit", false } };

	std::vector<std::pair<std::wstring, bool>> misc =
	{{L"Numpad-0------------DisableSave", false },
	{L"Numpad-1---DisableSaveNoMessage", false },
	{L"Numpad-2------OpenGameDirectory", false },
	{L"Numpad-3-----------OpenSettings", false },
	{L"Numpad-4---------ReloadSettings", false },
	{L"Numpad-5---------------MuteGame", false },
	{L"Numpad-6---------StickToProcess", false }};
	
	bool tune = false;
	waveOutSetVolume(NULL, 0xAAAAAAAA);
	if (reader.GetEntry("PlayTune").value_or("0") == "1") {
		PlaySound(MAKEINTRESOURCE(101), GetModuleHandle(NULL), SND_RESOURCE | SND_LOOP | SND_ASYNC);
		tune = true;
		menu[3].second = tune;
	}

	auto* cDialog = &menu;

	fnDialog(*cDialog);

	witness->AddEntry("XPos", 0x0062D0A8, { 0x148, 0x970, 0x228, 0x10, 0x50, 0x20, 0x30 }, 0x0);
	witness->AddEntry("YPos", 0x0062D0A8, { 0x148, 0x970, 0x228, 0x10, 0x50, 0x20, 0x30 }, 0x4);
	witness->AddEntry("ZPos", 0x0062D0A8, { 0x148, 0x970, 0x228, 0x10, 0x50, 0x20, 0x30 }, -0x4);
	witness->AddEntry("Speed", 0x0062D0A8, { 0x148, 0x970, 0x228, 0x10, 0x50, 0x20, 0x30 }, 0x10C);
	witness->AddEntry("UpDownRotPitch", 0x006303C0, {}, 0);
	witness->AddEntry("LeftRightRotYaw", 0x006303BC, {}, 0);
	
	bool fly, nosave, nosavemessage, nonodlimit, fastersprint, allsolutionswork, leavesolve, leavesolveenviroment, mutegame, sticktoprocess, hide;
	fly = nosave = nosavemessage = nonodlimit = fastersprint = allsolutionswork = leavesolve = leavesolveenviroment = mutegame = sticktoprocess = hide = false;

	bool menuAc = true, gamechangerAc, funAc, miscAc;
	gamechangerAc = funAc = miscAc = false;

	float x{}, y{}, z{};

	POINT windowPos{};

	while (witness->StillValid()) {		
		if (!hide) {
			if (input(VK_BACK)) {
				cDialog = &menu;
				fnDialog(*cDialog);
				menuAc = true;
				gamechangerAc = false;
				funAc = false;
				miscAc = false;
				Sleep(200);
			}
			if (input(VK_NUMPAD0)) {
				if (menuAc) {
					cDialog = &gamechanger;
					fnDialog(*cDialog);
					gamechangerAc = true;
					menuAc = false;
					funAc = false;
					miscAc = false;
					Sleep(200);
				}
				else if (gamechangerAc) {
					witness->Freeze();
					fly = !fly;
					fnFly(witness, fly);
					witness->Unfreeze();
					gamechanger[0].second = fly;
					fnDialog(*cDialog);
					Sleep(200);
				}
				else if (funAc) {
					nonodlimit = !nonodlimit;
					if (nonodlimit) witness->Patch("NoNodLimit", 0x14023CCA2, { 0x90,0x90,0x90,0x90 });
					else witness->Restore("NoNodLimit");
					fun[0].second = nonodlimit;
					fnDialog(*cDialog);
					Sleep(200);
				}
				else if (miscAc) {
					nosave = !nosave;
					if (nosave) witness->Patch("DisableSave", 0x140064C09, { 0x90, 0x90, 0x90, 0x90, 0x90 });
					else {
						witness->WriteAddress(0x140064C09, { 0xE8, 0x42, 0x17, 0x00, 0x00 });
						misc[1].second = false;
						nosavemessage = false;
					}
					misc[0].second = nosave;
					fnDialog(*cDialog);
					Sleep(200);
				}
			}
			if (input(VK_NUMPAD1)) {
				if (menuAc) {
					cDialog = &fun;
					fnDialog(*cDialog);
					funAc = true;
					menuAc = false;
					gamechangerAc = false;
					miscAc = false;
					Sleep(200);
				}
				else if (gamechangerAc) {
					fastersprint = !fastersprint;
					gamechanger[1].second = fastersprint;
					fnDialog(*cDialog);
					Sleep(200);
				}
				else if (miscAc) {
					nosavemessage = !nosavemessage;
					if (nosavemessage) witness->Patch("DisableSaveNoMessage", 0x140064C09, { 0xB8, 0x01, 0x00, 0x00, 0x00 });
					else {
						witness->WriteAddress(0x140064C09, { 0xE8, 0x42, 0x17, 0x00, 0x00 });
						misc[0].second = false;
						nosave = false;
					}
					misc[1].second = nosavemessage;
					fnDialog(*cDialog);
					Sleep(200);
				}

			}
			if (input(VK_NUMPAD2)) {
				if (menuAc) {
					cDialog = &misc;
					fnDialog(*cDialog);
					miscAc = true;
					menuAc = false;
					gamechangerAc = false;
					funAc = false;
					Sleep(200);
				}
				else if (gamechangerAc) {
					allsolutionswork = !allsolutionswork;
					if (allsolutionswork) witness->WriteAddress(0x1400BF552, { 0xC6, 0x45, 0x0F, 0x01, 0xB0, 0x01, 0x90 });
					else {
						witness->WriteAddress(0x1400BF552, { 0x88, 0x45, 0x0F, 0x84, 0xC0, 0x74, 0x6E });
						witness->WriteAddress(0x14022ECFA, { 0xE8, 0x91, 0xC1, 0xE8, 0xFF });
						gamechanger[3].second = false;
						leavesolve = false;
					}
					gamechanger[2].second = allsolutionswork;
					fnDialog(*cDialog);
					Sleep(200);
				}
				else if (miscAc) {
					DWORD size = MAX_PATH;
					char* filename = new char[MAX_PATH];
					QueryFullProcessImageNameA(witness->GetProcHandle(), 0, filename, &size);
					std::thread t1(system, (("explorer " + std::string(filename)).substr(0, ("explorer " + std::string(filename)).find_last_of("\\/"))).c_str());
					t1.detach();
					Sleep(200);
				}
			}
			if (input(VK_NUMPAD3)) {
				if (menuAc) {
					if (tune) PlaySound(NULL, NULL, SND_ASYNC);
					else PlaySound(MAKEINTRESOURCE(101), GetModuleHandle(NULL), SND_RESOURCE | SND_LOOP | SND_ASYNC);
					tune = !tune;
					menu[3].second = tune;
					fnDialog(*cDialog);
					Sleep(200);
				}
				if (gamechangerAc) {
					leavesolve = !leavesolve;
					if (leavesolve) {
						witness->WriteAddress(0x1400BF552, { 0xC6, 0x45, 0x0F, 0x01, 0xB0, 0x01, 0x90 });
						witness->WriteAddress(0x14022ECFA, { 0xE8, 0x31, 0x06, 0xE9, 0xFF });
					}
					else {
						witness->WriteAddress(0x1400BF552, { 0x88, 0x45, 0x0F, 0x84, 0xC0, 0x74, 0x6E });
						witness->WriteAddress(0x14022ECFA, { 0xE8, 0x91, 0xC1, 0xE8, 0xFF });
						gamechanger[2].second = false;
						allsolutionswork = false;
					}
					gamechanger[3].second = leavesolve;
					fnDialog(*cDialog);
					Sleep(200);
				}
				if (miscAc) {
					std::thread t1(system, "notepad C:\\Users\\Public\\Documents\\sTWTsettings.conf");
					t1.detach();
					Sleep(200);
				}
			}
			if (input(VK_NUMPAD4)) {
				if (menuAc) {
					fnRestoreAll(witness);
					CloseWindow(GetConsoleWindow());
					return 0;
				}
				if (gamechangerAc) {
					leavesolveenviroment = !leavesolveenviroment;
					if (leavesolveenviroment)
						witness->Patch("LeaveSolveEnviroment", 0x14022DCFF, { 0xC7, 0x87, 0xB8, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x41, 0xB4, 0x01 });
					else witness->Restore("LeaveSolveEnviroment");
					gamechanger[4].second = leavesolveenviroment;
					fnDialog(*cDialog);
					Sleep(200);
				}
				if (miscAc) {
					reader.Reload();
					Sleep(200);
				}
			}
			if (input(VK_NUMPAD5)) {
				if (gamechangerAc) {
					x = witness->Read<float>("XPos");
					y = witness->Read<float>("YPos");
					z = witness->Read<float>("ZPos");
					Sleep(200);
				}
				if (miscAc) {
					mutegame = !mutegame;
					if (mutegame) witness->Patch("MuteGame", 0x1402A94B0, { 0xC3, 0x90, 0x90 });
					else witness->Restore("MuteGame");
					misc[5].second = mutegame;
					fnDialog(*cDialog);
					Sleep(200);
				}
			}
			if (input(VK_NUMPAD6)) {
				if (gamechangerAc) {
					witness->Write("XPos", x);
					witness->Write("YPos", y);
					witness->Write("ZPos", z);
					Sleep(200);
				}
				if (miscAc) {
					lightDialog = !lightDialog;
					sticktoprocess = !sticktoprocess;
					if (sticktoprocess) {
						RECT r;
						GetWindowRect(GetConsoleWindow(), &r);
						windowPos.x = r.left;
						windowPos.y = r.top;
						SetWindowTextA(GetConsoleWindow(), "");
						auto alpha = reader.GetEntry("AlphaStickToProcess");
						if (alpha == std::nullopt)
							MessageBoxA(NULL, "AlphaStickToProcess no value", "Error", MB_ICONERROR);
						SetLayeredWindowAttributes(GetConsoleWindow(), NULL, std::stoi(alpha.value()), LWA_ALPHA);
						std::thread t1(fnStickToProcess, std::ref(sticktoprocess), std::ref(hide));
						t1.detach();
					}
					else {
						SetWindowTextA(GetConsoleWindow(), "-survivalizeed's-The-Witness-Trainer-");
						SetWindowPos(GetConsoleWindow(), HWND_NOTOPMOST, windowPos.x, windowPos.y, 0, 0, SWP_NOSIZE);
						SetLayeredWindowAttributes(GetConsoleWindow(), NULL, 255, LWA_ALPHA);
						ShowWindow(GetConsoleWindow(), SW_SHOW);
					}
					misc[6].second = sticktoprocess;
					fnDialog(*cDialog);
					Sleep(200);
				}
			}
		}
		if (input(VK_MULTIPLY)) {
			hide = !hide;
			if (hide)
				ShowWindow(GetConsoleWindow(), SW_HIDE);
			else
				ShowWindow(GetConsoleWindow(), SW_SHOW);
			Sleep(200);
		}
		if (input(VK_LSHIFT) && fastersprint) {
			auto speed = reader.GetEntry("SprintSpeed");
			if (speed == std::nullopt || speed == "") MessageBoxA(NULL, "SprintSpeed no value", "Error", MB_ICONERROR);
			else witness->Write<float>("Speed", std::stof(speed.value()));
		}
		if (input('W') && fly) {
			float pitch = witness->Read<float>("UpDownRotPitch");
			float yaw = witness->Read<float>("LeftRightRotYaw");
			float yp = witness->Read<float>("YPos");
			auto speed = reader.GetEntry("FlySpeed");
			if (speed == std::nullopt || speed == "") MessageBoxA(NULL, "FlySpeed no value", "Error", MB_ICONERROR);
			else {
				witness->Write("YPos", float(yp + (sinf(pitch) * 0.0001 * std::stof(speed.value()))));
				float xp = witness->Read<float>("XPos");
				witness->Write("XPos", float(xp + (sinf(yaw) * 0.0001 * std::stof(speed.value()))));
				float zp = witness->Read<float>("ZPos");
				witness->Write("ZPos", float(zp + (cosf(yaw) * 0.0001 * std::stof(speed.value()))));
			}
		}
	}
}
