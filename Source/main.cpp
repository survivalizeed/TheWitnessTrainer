#include "Includes.h"

using namespace mINI;

int main() {
	bool run = true;
	while (true) {
		system("CLS");
		static_cast<void>(_setmode(_fileno(stdout), _O_TEXT));
		{
			std::ifstream tuneCheck("C:\\Users\\Public\\Documents\\Tune.wav");
			std::ifstream askCheck("C:\\Users\\Public\\Documents\\sTWTnAsk");
			if (!tuneCheck.good() && !askCheck.good()) {
				int result = MessageBoxA(NULL, "Should the Trainer download it's Tune?", "Waiting for input...", MB_YESNO);
				if (result == IDYES) {
					std::cout << "Downloading tune...\n";
					if (S_OK == URLDownloadToFileA(NULL, "https://drive.google.com/uc?export=download&id=1-GiMg-RNpqr4Cudunu9tWZK9NkyDmeBI",
						"C:\\Users\\Public\\Documents\\Tune.wav", 0, NULL)) {
						std::cout << "Successfully downloaded the Tune. Enjoy it!\n";
						Sleep(2000);
						goto leave;
					}
					else {
						std::cout << "Failed to downloaded the Tune!\n";
						Sleep(2000);
					}
				}
				result = MessageBoxA(NULL, "Should the Trainer ask for a download again?", "Waiting for input...", MB_YESNO);
				if (result == IDNO) {
					std::ofstream("C:\\Users\\Public\\Documents\\sTWTnAsk");
				}
			}
		leave:;
		}

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
		witness->IdleWait("If some hacks don't work press Numpad 5 to reattach the Trainer!\nSearching for witness64_d3d11.exe ...", "Found witness64_d3d11.exe", [&]() {
			char* text = new char[MAX_PATH];
			int size = GetWindowTextA(_console, text, MAX_PATH);
			std::string str(text, size);
			SetWindowTextA(_console, (str + ".").c_str());
			delete[] text;
			if (std::count(str.begin(), str.end(), '.') >= 86) SetWindowTextA(_console, "Searching for witness64_d3d11.exe .");
			});
		witness->StartCheckThread();
		SetWindowTextA(_console, "-survivalizeed's-The-Witness-Trainer-");

		if (GetFileAttributes("C:\\Users\\Public\\Documents\\sTWTsettings.ini") == INVALID_FILE_ATTRIBUTES && GetLastError() == ERROR_FILE_NOT_FOUND) {
			MessageBoxA(NULL, "Customize the Trainers settings here: C:\\Users\\Public\\Documents\\sTWTsettings.ini", "Information", MB_ICONINFORMATION);
			INIFile file("C:\\Users\\Public\\Documents\\sTWTsettings.ini");
			INIStructure ini;
			ini["movement"]["flySpeed"] = "10";
			ini["movement"]["sprintSpeed"] = "20";
			ini["misc"]["playTuneOnStart"] = "1";
			ini["misc"]["alphaStickToProcess"] = "100";
			ini["misc"]["sprintKey"] = "0xA0";
			ini["misc"]["teleportForceInterval"] = "10";
			ini["misc"]["wAnimPath"] = "C:\\Users\\Public\\Downloads";
			file.generate(ini);
		}
		INIFile file("C:\\Users\\Public\\Documents\\sTWTsettings.ini");
		INIStructure ini;
		file.read(ini);

		Dialog dialog(L"-survivalizeed's-The-Witness-Trainer-");
		dialog.Set("menu", "gameChanger", { L"Numpad-0-----------------Game-Changer", false });
		dialog.Set("menu", "fun", { L"Numpad-1--------------------------Fun", false });
		dialog.Set("menu", "misc", { L"Numpad-2-------------------------Misc", false });
		dialog.Set("menu", "teleports", { L"Numpad-3--------------------Teleports", false });
		dialog.Set("menu", "animations", { L"Numpad-4-------------------Animations", false });
		dialog.Set("menu", "reattach", { L"Numpad-5---------------------Reattach", false });
		dialog.Set("menu", "tune", { L"Numpad-6-------------------------Tune", false });
		dialog.Set("menu", "quit", { L"Numpad-7-------------------------Quit", false });

		dialog.Set("gameChanger", "fly", { L"Numpad-0--------------------------Fly", false });
		dialog.Set("gameChanger", "fasterSprint", { L"Numpad-1----------------Faster-Sprint", false });
		dialog.Set("gameChanger", "allSolutionsWork", { L"Numpad-2-----------All-Solutions-Work", false });
		dialog.Set("gameChanger", "leaveSolve", { L"Numpad-3------------------Leave-Solve", false });
		dialog.Set("gameChanger", "leaveSolveEnviroment", { L"Numpad-4-------Leave-Solve-Enviroment", false });
		dialog.Set("gameChanger", "savePosition", { L"Numpad-5----------------Save-Position", false });
		dialog.Set("gameChanger", "moveToPosition", { L"Numpad-6-------------Move-To-Position", false });

		dialog.Set("fun", "noNodLimit", { L"Numpad-0-----------------No-Nod-Limit", false });

		dialog.Set("misc", "misc0", { L"Numpad-0-----------------------Misc-0", false });
		dialog.Set("misc", "misc1", { L"Numpad-1-----------------------Misc-1", false });

		dialog.Set("misc0", "disableSave", { L"Numpad-0-----------------Disable-Save", false });
		dialog.Set("misc0", "disableSaveNoMessage", { L"Numpad-1------Disable-Save-No-Message", false });
		dialog.Set("misc0", "openGameDirectory", { L"Numpad-2----------Open-Game-Directory", false });
		dialog.Set("misc0", "openSettings", { L"Numpad-3----------------Open-Settings", false });
		dialog.Set("misc0", "reloadSettings", { L"Numpad-4--------------Reload-Settings", false });
		dialog.Set("misc0", "muteGame", { L"Numpad-5--------------------Mute-Game", false });
		dialog.Set("misc0", "stickToProcess", { L"Numpad-6-------------Stick-To-Process", false });
		dialog.Set("misc0", "installHackedSave", { L"Numpad-7----------Install-Hacked-Save", false });
		dialog.Set("misc0", "disableStartDialog", { L"Numpad-8---------Disable-Start-Dialog", false });
		dialog.Set("misc0", "enableStartDialog", { L"Numpad-9----------Enable-Start-Dialog", false });

		dialog.Set("misc1", "changeSaveGamePath", { L"Numpad-0---------Change-Savegame-Path", false });
		dialog.Set("misc1", "revertSaveGamePath", { L"Numpad-1---------Revert-Savegame-Path", false });

		dialog.Set("teleports", "teleports0", { L"Numpad-0------------------Teleports-0", false });
		dialog.Set("teleports", "teleports1", { L"Numpad-1------------------Teleports-1", false });

		dialog.Set("teleports0", "tutorial", { L"Numpad-0---------------------Tutorial", false });
		dialog.Set("teleports0", "turntable", { L"Numpad-1--------------------Turntable", false });
		dialog.Set("teleports0", "top", { L"Numpad-2--------------------------Top", false });
		dialog.Set("teleports0", "ruin", { L"Numpad-3-------------------------Ruin", false });
		dialog.Set("teleports0", "end", { L"Numpad-4--------------------------End", false });
		dialog.Set("teleports0", "stoneWoman", { L"Numpad-5------------------Stone-Woman", false });
		dialog.Set("teleports0", "oceanChair", { L"Numpad-6------------------Ocean-Chair", false });
		dialog.Set("teleports0", "handReach", { L"Numpad-7-------------------Hand-Reach", false });
		dialog.Set("teleports0", "turtle", { L"Numpad-8-----------------------Turtle", false });
		dialog.Set("teleports0", "endElevator", { L"Numpad-9-----------------End-Elevator", false });

		dialog.Set("teleports1", "woodenView", { L"Numpad-0------------------Wooden-View", false });

		dialog.Set("animations", "addCurrentPosNode", { L"Numpad-0----Add-Current-Position-Node", false });
		dialog.Set("animations", "loadWAnimFile", { L"Numpad-1--------------Load-wAnim-File", false });
		dialog.Set("animations", "writeWAnimFile", { L"Numpad-2-------------Write-wAnim-File", false });
		dialog.Set("animations", "playCurrentAnimation", { L"Numpad-3-------Play-Current-Animation", false });
		dialog.Set("animations", "clearCurrentAnimation", { L"Numpad-4------Clear-Current-Animation", false });

		dialog.PushDialog(dialog.GetDialog("menu"));

		waveOutSetVolume(NULL, 0xAAAAAAAA);
		if (ini["misc"]["playTuneOnStart"] != "0") {
			PlaySound("C:\\Users\\Public\\Documents\\Tune.wav", GetModuleHandle(NULL), SND_LOOP | SND_ASYNC);
			dialog.Set("menu", "tune", { L"", true });
		}

		witness->AddEntry("XPos", 0x0062D0A8, { 0x148, 0x970, 0x228, 0x10, 0x50, 0x20, 0x30 }, 0x0);
		witness->AddEntry("YPos", 0x0062D0A8, { 0x148, 0x970, 0x228, 0x10, 0x50, 0x20, 0x30 }, 0x4);
		witness->AddStaticEntry("YCamPos", 0x140630498);
		witness->AddEntry("ZPos", 0x0062D0A8, { 0x148, 0x970, 0x228, 0x10, 0x50, 0x20, 0x30 }, -0x4);
		witness->AddEntry("Speed", 0x0062D0A8, { 0x148, 0x970, 0x228, 0x10, 0x50, 0x20, 0x30 }, 0x10C);
		witness->AddStaticEntry("UpDownRotPitch", 0x1406303C0);
		witness->AddStaticEntry("LeftRightRotYaw", 0x1406303BC);

		bool hide = false;

		float x, y, z;
		x = y = z = 0.f;

		int sprintKey{};

		Animation currentAnimation(witness);

		fnSprintKey(witness, ini, sprintKey);

		POINT windowPos{};

		run = true;
		std::thread tFlyControls(fnFlyControls, std::ref(witness), std::ref(dialog), std::ref(ini), std::ref(run));
		tFlyControls.detach();
		std::thread tStickToProcess(fnStickToProcess, std::ref(dialog), std::ref(hide), std::ref(run));
		tStickToProcess.detach();
		std::thread tSprintControls(fnSprintControls, std::ref(witness), std::ref(dialog), std::ref(ini), std::ref(sprintKey), std::ref(run));
		tSprintControls.detach();

		while (witness->StillValid()) {
			if (!hide) {
				if (input(VK_BACK)) {
					dialog.PopDialog();
					Sleep(200);
				}
				if (input(VK_NUMPAD0)) {
					if (dialog.GetDialog("menu") == dialog.GetCurrentDialog()) {
						dialog.PushDialog(dialog.GetDialog("gameChanger"));
					}
					else if (dialog.GetDialog("teleports") == dialog.GetCurrentDialog()) {
						dialog.PushDialog(dialog.GetDialog("teleports0"));
					}
					else if (dialog.GetDialog("gameChanger") == dialog.GetCurrentDialog()) {
						dialog.InvertEntry("gameChanger", "fly");
						fnRemAutoPosition(witness, dialog.GetEntry("gameChanger", "fly")->second);
					}
					else if (dialog.GetDialog("fun") == dialog.GetCurrentDialog()) {
						dialog.InvertEntry("fun", "noNodLimit");
						if (dialog.GetEntry("fun", "noNodLimit")->second)
							witness->Patch("NoNodLimit", 0x14023CCA2, { 0x90,0x90,0x90,0x90 });
						else
							witness->Restore("NoNodLimit");
					}
					else if (dialog.GetDialog("misc") == dialog.GetCurrentDialog()) {
						dialog.PushDialog(dialog.GetDialog("misc0"));
					}
					else if (dialog.GetDialog("misc0") == dialog.GetCurrentDialog()) {
						dialog.InvertEntry("misc0", "disableSave");
						if (dialog.GetEntry("misc0", "disableSave")->second)
							witness->Patch("DisableSave", 0x140064C09, { 0x90, 0x90, 0x90, 0x90, 0x90 });
						else {
							witness->WriteAddress(0x140064C09, { 0xE8, 0x42, 0x17, 0x00, 0x00 });
							dialog.Set("misc0", "disableSaveNoMessage", { L"", false });
						}
					}
					else if (dialog.GetDialog("misc1") == dialog.GetCurrentDialog()) {
						fnChangeSavegamePath(witness, false);
						dialog.DisplayDialog();
					}
					else if (dialog.GetDialog("teleports0") == dialog.GetCurrentDialog()) {
						fnTeleport(witness, dialog, ini, -164.53f, 5.74332f, -133.377f, 0.0653167f, 2.88611f);
					}
					else if (dialog.GetDialog("teleports1") == dialog.GetCurrentDialog()) {
						fnTeleport(witness, dialog, ini, -42.4168f, 35.6578f, 142.355f, -0.0908066f, 1.76752f);
					}
					else if (dialog.GetDialog("animations") == dialog.GetCurrentDialog()) {
						currentAnimation.AddPosNode();
					}
					Sleep(200);
				}
				if (input(VK_NUMPAD1)) {
					if (dialog.GetDialog("menu") == dialog.GetCurrentDialog()) {
						dialog.PushDialog(dialog.GetDialog("fun"));
					}
					else if (dialog.GetDialog("teleports") == dialog.GetCurrentDialog()) {
						dialog.PushDialog(dialog.GetDialog("teleports0"));
					}
					else if (dialog.GetDialog("gameChanger") == dialog.GetCurrentDialog()) {
						dialog.InvertEntry("gameChanger", "fasterSprint");
					}
					else if (dialog.GetDialog("misc") == dialog.GetCurrentDialog()) {
						dialog.PushDialog(dialog.GetDialog("misc1"));
					}
					else if (dialog.GetDialog("misc0") == dialog.GetCurrentDialog()) {
						dialog.InvertEntry("misc0", "disableSaveNoMessage");
						if (dialog.GetEntry("misc0", "disableSaveNoMessage")->second)
							witness->Patch("DisableSaveNoMessage", 0x140064C09, { 0xB8, 0x01, 0x00, 0x00, 0x00 });
						else {
							witness->WriteAddress(0x140064C09, { 0xE8, 0x42, 0x17, 0x00, 0x00 });
							dialog.Set("misc0", "disableSave", { L"", false });
						}
					}
					else if (dialog.GetDialog("misc1") == dialog.GetCurrentDialog()) {
						fnChangeSavegamePath(witness, true);
						dialog.DisplayDialog();
					}
					else if (dialog.GetDialog("teleports0") == dialog.GetCurrentDialog()) {
						fnTeleport(witness, dialog, ini, -31.3635f, -11.7304f, -38.6826f, -0.402977f, -0.0448767f);
					}
					else if (dialog.GetDialog("animations") == dialog.GetCurrentDialog()) {
						system("CLS");
						SetForegroundWindow(_console);
						std::wcout << "File name: ";
						std::wstring input;
						std::wcin.clear();
						std::wcin >> input;
						currentAnimation.LoadwAnim(ini["misc0"]["wAnimPath"] + "\\" + std::string(input.begin(), input.end()));
						dialog.DisplayDialog();
					}
					Sleep(200);
				}
				if (input(VK_NUMPAD2)) {
					if (dialog.GetDialog("menu") == dialog.GetCurrentDialog()) {
						dialog.PushDialog(dialog.GetDialog("misc"));
					}
					else if (dialog.GetDialog("gameChanger") == dialog.GetCurrentDialog()) {
						dialog.InvertEntry("gameChanger", "allSolutionsWork");
						if (dialog.GetEntry("gameChanger", "allSolutionsWork")->second)
							witness->WriteAddress(0x1400BF552, { 0xC6, 0x45, 0x0F, 0x01, 0xB0, 0x01, 0x90 });
						else {
							witness->WriteAddress(0x1400BF552, { 0x88, 0x45, 0x0F, 0x84, 0xC0, 0x74, 0x6E });
							witness->WriteAddress(0x14022ECFA, { 0xE8, 0x91, 0xC1, 0xE8, 0xFF });
							dialog.Set("gameChanger", "leaveSolve", { L"", false });
						}
					}
					else if (dialog.GetDialog("misc0") == dialog.GetCurrentDialog()) {
						DWORD size = MAX_PATH;
						char* filename = new char[MAX_PATH];
						QueryFullProcessImageNameA(witness->GetProcHandle(), 0, filename, &size);
						std::thread t1(system, (("explorer " + std::string(filename)).substr(0, ("explorer " + std::string(filename)).find_last_of("\\/"))).c_str());
						t1.detach();
						delete[] filename;
					}
					else if (dialog.GetDialog("teleports0") == dialog.GetCurrentDialog()) {
						fnTeleport(witness, dialog, ini, -51.6206f, 66.8419f, 144.698f, -0.182666f, 2.82946f);
					}
					else if (dialog.GetDialog("animations") == dialog.GetCurrentDialog()) {
						system("CLS");
						SetForegroundWindow(_console);
						std::wcout << "File name: ";
						std::wstring input;
						std::wcin.clear();
						std::wcin >> input;
						currentAnimation.TowAnim(ini["misc0"]["wAnimPath"] + "\\" + std::string(input.begin(), input.end()));
						dialog.DisplayDialog();
					}
					Sleep(200);
				}
				if (input(VK_NUMPAD3)) {
					if (dialog.GetDialog("menu") == dialog.GetCurrentDialog()) {
						dialog.PushDialog(dialog.GetDialog("teleports"));
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
					}
					else if (dialog.GetDialog("misc0") == dialog.GetCurrentDialog()) {
						std::thread t1(system, "notepad C:\\Users\\Public\\Documents\\sTWTsettings.ini");
						t1.detach();
					}
					else if (dialog.GetDialog("teleports0") == dialog.GetCurrentDialog()) {
						fnTeleport(witness, dialog, ini, 135.093f, 39.3168f, 54.3465f, -0.334823f, -1.75872f);
					}
					else if (dialog.GetDialog("animations") == dialog.GetCurrentDialog()) {
						currentAnimation.StartAnimation(dialog);
					}
					Sleep(200);
				}
				if (input(VK_NUMPAD4)) {
					if (dialog.GetDialog("menu") == dialog.GetCurrentDialog()) {
						dialog.PushDialog(dialog.GetDialog("animations"));
					}
					else if (dialog.GetDialog("gameChanger") == dialog.GetCurrentDialog()) {
						dialog.InvertEntry("gameChanger", "leaveSolveEnviroment");
						if (dialog.GetEntry("gameChanger", "leaveSolveEnviroment")->second)
							witness->Patch("LeaveSolveEnviroment", 0x14022DCFF, { 0xC7, 0x87, 0xB8, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x41, 0xB4, 0x01 });
						else
							witness->Restore("LeaveSolveEnviroment");
					}
					else if (dialog.GetDialog("misc0") == dialog.GetCurrentDialog()) {
						file.read(ini);
						fnSprintKey(witness, ini, sprintKey);
					}
					else if (dialog.GetDialog("teleports0") == dialog.GetCurrentDialog()) {
						fnTeleport(witness, dialog, ini, -49.1121f, -0.0246615f, 206.573f, -0.0136076f, -3.01675f);
					}
					else if (dialog.GetDialog("animations") == dialog.GetCurrentDialog()) {
						currentAnimation.Clear();
					}
					Sleep(200);
				}
				if (input(VK_NUMPAD5)) {
					if (dialog.GetDialog("menu") == dialog.GetCurrentDialog()) {
						fnRestoreAll(witness);
						break;
					}
					else if (dialog.GetDialog("gameChanger") == dialog.GetCurrentDialog()) {
						x = witness->Read<float>("XPos");
						y = witness->Read<float>("YPos");
						z = witness->Read<float>("ZPos");
					}
					else if (dialog.GetDialog("misc0") == dialog.GetCurrentDialog()) {
						dialog.InvertEntry("misc0", "muteGame");
						if (dialog.GetEntry("misc0", "muteGame")->second)
							witness->Patch("MuteGame", 0x1402A94B0, { 0xC3, 0x90, 0x90 });
						else
							witness->Restore("MuteGame");
					}
					else if (dialog.GetDialog("teleports0") == dialog.GetCurrentDialog()) {
						fnTeleport(witness, dialog, ini, 125.004f, 0.477013f, 177.684f, 0.0322629f, -2.10936f);
					}
					Sleep(200);
				}
				if (input(VK_NUMPAD6)) {
					if (dialog.GetDialog("menu") == dialog.GetCurrentDialog()) {
						if (dialog.GetEntry("menu", "tune")->second)
							PlaySound(NULL, NULL, SND_ASYNC);
						else
							PlaySound("C:\\Users\\Public\\Documents\\Tune.wav", GetModuleHandle(NULL), SND_LOOP | SND_ASYNC);
						dialog.InvertEntry("menu", "tune");
					}
					if (dialog.GetDialog("gameChanger") == dialog.GetCurrentDialog()) {
						if (x != 0 && y != 0 && z != 0) {
							fnTeleport(witness, dialog, ini, x, y, z, witness->Read<float>("LeftRightRotYaw"), witness->Read<float>("UpDownRotPitch"));
						}
					}
					else if (dialog.GetDialog("misc0") == dialog.GetCurrentDialog()) {
						dialog.compactMode = !dialog.compactMode;
						dialog.InvertEntry("misc0", "stickToProcess");
						if (dialog.GetEntry("misc0", "stickToProcess")->second) {
							RECT r;
							GetWindowRect(_console, &r);
							windowPos.x = r.left;
							windowPos.y = r.top;
							SetWindowTextA(_console, "");
							if (ini["misc0"]["alphaStickToProcess"].empty()) {
								error("alphaSticktoProcess no value!", witness);
							}
							try {
								SetLayeredWindowAttributes(_console, NULL, std::stoi(ini["misc0"]["alphaStickToProcess"]), LWA_ALPHA);
							}
							catch (...) {
								error("alphaStickToProcess illegal value!", witness);
							}
						}
						else {
							Sleep(100);
							SetWindowTextA(_console, "-survivalizeed's-The-Witness-Trainer-");
							SetWindowPos(_console, HWND_NOTOPMOST, windowPos.x, windowPos.y, 0, 0, SWP_NOSIZE);
							SetLayeredWindowAttributes(_console, NULL, 255, LWA_ALPHA);
							ShowWindow(_console, SW_SHOW);
						}
					}
					else if (dialog.GetDialog("teleports0") == dialog.GetCurrentDialog()) {
						fnTeleport(witness, dialog, ini, 211.974f, 9.97759f, 73.6323f, 0.102589f, 1.60719f);
					}
					Sleep(200);
				}
				if (input(VK_NUMPAD7)) {
					if (dialog.GetDialog("menu") == dialog.GetCurrentDialog()) {
						fnRestoreAll(witness);
						CloseWindow(_console);
						std::cout << "Trainer Closed...";
						return 0;
					}
					else if (dialog.GetDialog("misc0") == dialog.GetCurrentDialog()) {
						char username[256 + 1];
						DWORD username_len = 256 + 1;
						GetUserNameA(username, &username_len);
						fnExportRes(IDR_WCS1, "WCS",
							std::string("C:\\Users\\" + std::string(username) + "\\AppData\\Roaming\\The Witness\\TrainerSaveGame.witness_campaign").c_str());
						fnExportRes(IDB_PNG1, "PNG",
							std::string("C:\\Users\\" + std::string(username) + "\\AppData\\Roaming\\The Witness\\TrainerSaveGame.png").c_str());
					}
					else if (dialog.GetDialog("teleports0") == dialog.GetCurrentDialog()) {
						fnTeleport(witness, dialog, ini, 8.152f, 0.565118f, 211.562f, 0.474406f, -2.83249f);
					}
					Sleep(200);
				}
				if (input(VK_NUMPAD8)) {
					if (dialog.GetDialog("misc0") == dialog.GetCurrentDialog()) {
						int result = MessageBoxA(NULL, "This will restart The Witness! Do you want to continue?", "Waiting for input...", MB_YESNO);
						if (result == IDYES) {
							witness->DiskPatch(0x35EEAE, { 0xEB });
						}
					}
					else if (dialog.GetDialog("teleports0") == dialog.GetCurrentDialog()) {
						fnTeleport(witness, dialog, ini, -43.3622f, 20.1339f, 68.5811f, 0.010124f, 0.978153f);
					}
					Sleep(200);
				}
				if (input(VK_NUMPAD9)) {
					if (dialog.GetDialog("misc0") == dialog.GetCurrentDialog()) {
						int result = MessageBoxA(NULL, "This will restart The Witness! Do you want to continue?", "Waiting for input...", MB_YESNO);
						if (result == IDYES) {
							witness->DiskPatch(0x35EEAE, { 0x74 });
						}
					}
					else if (dialog.GetDialog("teleports0") == dialog.GetCurrentDialog()) {
						fnTeleport(witness, dialog, ini, -48.6889f, -2.96041f, 212.258f, -0.0250394f, -3.06025f);
					}
					Sleep(200);
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
			if (input(VK_F5)) {
				std::wcout << witness->Read<float>("XPos") << " " << witness->Read<float>("YPos") << " " << witness->Read<float>("ZPos") << "\n";
				std::wcout << witness->Read<float>("UpDownRotPitch") << " " << witness->Read<float>("LeftRightRotYaw");
				Sleep(200);
			}
		}
		run = false;
		Sleep(100);
	}
}