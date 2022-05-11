#pragma once
#include <fstream>
#include <iostream>
#include <sstream>
#include <string_view>
#include <vector>
#include <optional>

class SCR {
private:
	std::vector<std::string> buf;
	std::string_view path;
public:
	SCR(std::string_view path) 
		: path(path)
	{
		Reload();
	}
	
	std::optional<std::string> GetEntry(std::string_view name) {
		std::string entry = "";
		for (auto& iter : buf) if (iter.find(name) != std::string::npos) entry = iter;
		if (entry == "") return std::nullopt;
		entry = entry.substr(entry.find("=") + 1);
		return entry;
	}

	void Reload() {
		buf.clear();
		std::ifstream reader(path.data());
		std::stringstream ss;
		ss << reader.rdbuf();
		std::string tmp;
		while (std::getline(ss, tmp, ';')) {
			tmp.erase(std::remove(tmp.begin(), tmp.end(), '\n'), tmp.end());
			buf.push_back(tmp);
		}
	}
};