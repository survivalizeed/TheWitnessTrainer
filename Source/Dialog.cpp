#include "Dialog.h"

#pragma warning(disable: 4018)
#pragma warning(disable: 4267)

Dialog::Dialog(dString title)
{
	this->title = title;
	this->overallStrLen = title.size() + 2;
#ifdef UNICODE
	static_cast<void>(_setmode(_fileno(stdout), _O_U16TEXT));
	empty = L' ';
	newLine = L'\n';
	border1 = L'\u2588';
	border2 = L'\u2593';
	border3 = L'\u2592';
	border4 = L'\u2591';
	titleC = L'\u058D';
#else

#endif
}

void Dialog::Set(std::string_view dialog, std::string_view entry, const tySingleEntry& obj)
{
	if (obj.first.empty())
		dialogs[dialog.data()][entry.data()].second = obj.second;
	else
		dialogs[dialog.data()][entry.data()] = obj;
	if (!std::count(order[&dialogs[dialog.data()]].begin(), order[&dialogs[dialog.data()]].end(), &dialogs[dialog.data()][entry.data()])) 
		order[&dialogs[dialog.data()]].push_back(&dialogs[dialog.data()][entry.data()]);
	else
		DisplayDialog();
}

void Dialog::PushDialog(const tyDialogEntry* dialog) 
{
	if (!firstInit) {
		rootDialog = dialog;
		firstInit = true;
	}
	history.push(dialog);
	DisplayDialog();
}

void Dialog::PopDialog() 
{
	if (history.top() == rootDialog) {
		while (!history.empty())
			history.pop();
		history.push(rootDialog);
	}
	else
		history.pop();
	DisplayDialog();
}

const Dialog::tyDialogEntry* Dialog::GetDialog(std::string_view dialog)
{
	return &dialogs[dialog.data()];
}

const Dialog::tySingleEntry* Dialog::GetEntry(std::string_view dialog, std::string_view entry) 
{
	return &dialogs[dialog.data()][entry.data()];
}

void Dialog::InvertEntry(std::string_view dialog, std::string_view entry)
{
	dialogs[dialog.data()][entry.data()].second = !dialogs[dialog.data()][entry.data()].second;
	DisplayDialog();
}

const Dialog::tyDialogEntry* Dialog::GetCurrentDialog() 
{
	return history.top();
}

void Dialog::DisplayDialog()
{
	HWND hConsole = GetConsoleWindow();
	auto& rDialog = *history.top();

	auto compact = [&]() {
		SetWindowPos(hConsole, NULL, 0, 0, 9 * (overallStrLen + 3), 39 + 16 * static_cast<int>(rDialog.size()), SWP_NOMOVE);
		dString buf;
		for (auto& iter : order[&rDialog]) {
			buf += iter->first;
			if (iter->second)
				buf += dString() + empty + empty + empty + border1 + border1 + border1;
			buf += newLine;
		}
		buf.erase(buf.size() - 1);
		print(buf);
	};
	auto full = [&]() {
		SetWindowPos(hConsole, NULL, 0, 0, 9 * (overallStrLen + 37), 119 + 16 * static_cast<int>(rDialog.size()), SWP_NOMOVE);
		dString begin, end, buf;
		begin += dString() + border4 + border4 + border3 + border3 + border2 + border1 + border1 + border1 + border1 + border1;
		end += dString() + border1 + border1 + border1 + border1 + border1 + border2 + border3 + border3 + border4 + border4;
		buf += dString() + empty + empty + empty + empty + empty + empty + empty + empty;
		buf += begin;
		for (int i = 0; i < overallStrLen + 4; ++i) buf += border1;
		buf += dString() + end + newLine;
		buf += dString() + empty + empty + empty + empty;
		buf += begin;
		for (int i = 0; i < overallStrLen + 12; ++i) buf += border1;
		buf += dString() + end + newLine;
		buf += begin;
		for (int i = 0; i < 11; ++i) buf += titleC;
		buf += title;
		for (int i = 0; i < 11; ++i) buf += titleC;
		buf += dString() + end + newLine;
		for (auto& iter : order[&rDialog]) {
			dString tmp = iter->first;
			dString tmpBegin{}, tmpEnd{};
			if (iter->second) {
				tmpBegin = dString() + border1 + border1 + border2 + border2 + border3 + border4;
				for (int i = 0; i < 11 - 6; ++i) tmpBegin += empty;
				for (int i = 0; i < 11 - 6; ++i) tmpEnd += empty;
				tmpEnd += dString() + border4 + border3 + border2 + border2 + border1 + border1;
			}
			else {
				for (int i = 0; i < 11; ++i) tmpBegin += empty;
				for (int i = 0; i < 11; ++i) tmpEnd += empty;
			}
			tmp.insert(0, tmpBegin);
			tmp.insert(tmp.size(), tmpEnd);
			buf += dString() + begin + tmp + end + newLine;
		}
		buf += dString() + empty + empty + empty + empty;
		buf += begin;
		for (int i = 0; i < overallStrLen + 12; ++i) buf += border1;
		buf += dString() + end + newLine;
		buf += dString() + empty + empty + empty + empty + empty + empty + empty + empty;
		buf += begin;
		for (int i = 0; i < overallStrLen + 4; ++i) buf += border1;
		buf += end;
		print(buf);
	};
	system("CLS");
	if (compactMode)
		compact();
	else
		full();
}


