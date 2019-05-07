#pragma once
#include <string>
#include <fstream>
#include <locale>
#include <codecvt>

namespace pol_sim {
	std::wstring search_until(std::wifstream& file, std::wstring chars, wchar_t& last_char);
	std::wstring search_until_exact(std::wifstream& file, std::wstring match);
	void seek_until_exact(std::wifstream& file, std::wstring match);
	void seek_until(std::wifstream& file, std::wstring chars, wchar_t& last_char);
	std::wstring load_quotes(std::wifstream& file, wchar_t& last_char);
	//Locates and reads in everything between quotes
}