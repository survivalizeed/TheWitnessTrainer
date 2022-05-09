#include <iostream>
#define _USE_MATH_DEFINES
#include <math.h>
#include <memory>
#include <string>
#include <fcntl.h>
#include <io.h>
#include "Trainer.h"

#define log(x)\
std::cout << x << "\n"
#define input(key)\
GetAsyncKeyState(key) & 0x8000

void fnDialog(const std::vector<std::pair<std::wstring, bool>>& entrys) {
	system("CLS");
	static_cast<void>(_setmode(_fileno(stdout), _O_U16TEXT));
	std::wstring begin = L" \u2591\u2591\u2592\u2592\u2593\u2588\u2588\u2588\u2588\u2588";
	std::wstring end = L"\u2588\u2588\u2588\u2588\u2588\u2593\u2592\u2592\u2591\u2591";
	std::wstring buf;
	buf += L"        " + begin;
	for (int i = 0; i < 36; ++i) buf += L"\u2588";
	buf += end + L"\n";
	buf += L"    " + begin;
	for (int i = 0; i < 44; ++i) buf += L"\u2588";
	buf += end + L"\n";
	buf += begin + L"-----------------The-Witness-Trainer-----------------" + end + L"\n";
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
	buf += end + L"\n";
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

int main() {
	std::shared_ptr<Trainer> witness = std::make_shared<Trainer>("witness64_d3d11.exe");
	witness->IdleWait("You have to be ingame before you open the trainer!\nSearching for witness64_d3d11.exe ...", "Found witness64_d3d11.exe");
	
	std::vector<std::pair<std::wstring, bool>> menu = 
	{{L"Numpad-0------------GameChanger", false},
	{L"Numpad-1--------------------Fun", false},
	{L"Numpad-2-------------------Misc", false}};
	
	std::vector<std::pair<std::wstring, bool>> gamechanger =
	{{L"Numpad-0--------------------Fly", false},
	{L"Numpad-1-----------FasterSprint", false },
	{L"Numpad-2-------AllSolutionsWork", false } };

	std::vector<std::pair<std::wstring, bool>> fun =
	{ {L"Numpad-0-------------NoNodLimit", false } };

	std::vector<std::pair<std::wstring, bool>> misc =
	{{L"Numpad-0------------DisableSave", false },
	{L"Numpad-1---DisableSaveNoMessage", false },
	{L"Numpad-2----------OpenDirectory", false } };
	
	auto* cDialog = &menu;

	fnDialog(*cDialog);

	witness->AddEntry("XPos", 0x0062D0A8, { 0x148, 0x970, 0x228, 0x10, 0x50, 0x20, 0x30 }, 0x0);
	witness->AddEntry("YPos", 0x0062D0A8, { 0x148, 0x970, 0x228, 0x10, 0x50, 0x20, 0x30 }, 0x4);
	witness->AddEntry("ZPos", 0x0062D0A8, { 0x148, 0x970, 0x228, 0x10, 0x50, 0x20, 0x30 }, -0x4);
	witness->AddEntry("Speed", 0x0062D0A8, { 0x148, 0x970, 0x228, 0x10, 0x50, 0x20, 0x30 }, 0x10C);
	witness->AddEntry("UpDownRotPitch", 0x006303C0, {}, 0);
	witness->AddEntry("LeftRightRotYaw", 0x006303BC, {}, 0);
	
	bool fly, nosave, nosavemessage, nonodlimit, fastersprint, allsolutionswork;
	fly = nosave = nosavemessage = nonodlimit = fastersprint = allsolutionswork = false;

	bool menuAc = true, gamechangerAc, funAc, miscAc;
	gamechangerAc = funAc = miscAc = false;
	for (;;) {	
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
				else witness->WriteAddress(0x140064C09, { 0xE8, 0x42, 0x17, 0x00, 0x00 });
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
				else witness->WriteAddress(0x140064C09, { 0xE8, 0x42, 0x17, 0x00, 0x00 });
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
				if (allsolutionswork) witness->Patch("AllSolutions", 0x1400BF552, { 0xC6, 0x45, 0x0F, 0x01, 0xB0, 0x01, 0x90 });
				else witness->Restore("AllSolutions");
				gamechanger[2].second = allsolutionswork;
				fnDialog(*cDialog);
				Sleep(200);
			}
			else if (miscAc) {
				DWORD size = MAX_PATH;
				char* filename = new char[MAX_PATH];
				QueryFullProcessImageNameA(witness->GetProcHandle(), 0, filename, &size);
				system(("explorer " + std::string(filename)).substr(0, ("explorer " + std::string(filename)).find_last_of("\\/")).c_str());
				Sleep(200);
			}
		}
		if (input(VK_LSHIFT) && fastersprint) {
			witness->Write<float>("Speed", float(15));
		}
		if (input('W') && fly) {
			float pitch = witness->Read<float>("UpDownRotPitch");
			float yaw = witness->Read<float>("LeftRightRotYaw");
			float yp = witness->Read<float>("YPos");
			witness->Write("YPos", float(yp + (sinf(pitch) * 0.01)));
			float xp = witness->Read<float>("XPos");
			witness->Write("XPos", float(xp + (sinf(yaw) * 0.01)));
			float zp = witness->Read<float>("ZPos");
			witness->Write("ZPos", float(zp + (cosf(yaw) * 0.01)));
		}
	}

}