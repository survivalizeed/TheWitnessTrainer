#pragma once

#include "Includes.h"

class Dialog {

#ifdef UNICODE
	using dString = std::wstring;
	using dChar = wchar_t;
#define print(x)\
std::wcout << x
#else
	using dString = std::string;
	using dChar = char;
#define print(x)\
std::cout << x
#endif
	using tyDialog = std::map<std::string, std::map<std::string, std::pair<dString, bool>>>;
	using tyDialogEntry = std::map<std::string, std::pair<dString, bool>>;
	using tySingleEntry = std::pair<dString, bool>;
	std::map<const tyDialogEntry*, std::vector<tySingleEntry*>> order;

	bool firstInit = false;
	tyDialog dialogs;
	dString title;
	dChar empty, newLine;
	unsigned overallStrLen;

	std::stack<const tyDialogEntry*> history{};
	const tyDialogEntry* rootDialog = nullptr;

public:
	bool compactMode = false;
	dChar border1, border2, border3, border4, titleC;
	
	Dialog(dString title);

	void Set(std::string_view dialog, std::string_view entry, const tySingleEntry& obj);

	const tyDialogEntry* GetDialog(std::string_view dialog);

	const tySingleEntry* GetEntry(std::string_view dialog, std::string_view entry);

	void InvertEntry(std::string_view dialog, std::string_view entry);

	void PushDialog(const tyDialogEntry* dialog);

	void PopDialog();

	const tyDialogEntry* GetCurrentDialog();

	void DisplayDialog();

};