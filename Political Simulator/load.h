#pragma once
#include <fstream>
#include <string>
#include <locale>
#include <codecvt>
#include <algorithm>

namespace pol_sim {
	wchar_t get_with_ignore(std::wifstream& file, const std::wstring& ignore); //replaces .get() with a function that will ignore the remanining characters to \n if it encounters any characters from ignore
	void ignore_white_space(std::wifstream& file);
	std::wstring search_until(std::wifstream& file, const std::wstring& chars, wchar_t& last_char);
	void seek_until(std::wifstream& file, const std::wstring& chars, wchar_t& last_char);
	std::wstring search_until_exact(std::wifstream& file, const std::wstring& match);
	void seek_until_exact(std::wifstream& file, std::wstring match);
	std::wstring search_until_exact(std::wifstream& file, const std::initializer_list<std::wstring>& match_list, std::wstring& last_match);
	void seek_until_exact(std::wifstream& file, const std::initializer_list<std::wstring>& match_list, std::wstring& last_match);
	std::wstring load_quotes(std::wifstream& file, wchar_t& last_char);
	//Locates and reads in everything between quotes
}