#pragma once
//Functions that are called in multiple class files
#include "load.h"
namespace pol_sim {
	wchar_t get_with_ignore(std::wifstream& file, const std::wstring& ignore) //replaces .get() with a function that will ignore the remanining characters to \n if it encounters any characters from ignore
	{
		wchar_t chr = 0;
		std::wstring throw_away;
		while (file.good() && ignore.find(chr = file.get()) != std::wstring::npos) { //If the character is in ignore keep repeating getline until we no longer find the character
			std::getline(file, throw_away);
		}
		return chr;
	}
	void ignore_white_space(std::wifstream& file) {
		while (file.good() && std::wstring(L"\t \n").find(file.peek()) == std::wstring::npos)
			get_with_ignore(file, L"#");
	}
	std::wstring search_until(std::wifstream & file, const std::wstring & chars, wchar_t& last_char) {
		std::wstring final_text;
		file.imbue(std::locale(file.getloc(), new std::codecvt_utf16<wchar_t, 0x10ffff, std::little_endian>()));
		while (file.good() && chars.find(last_char = get_with_ignore(file, L"#")) == std::wstring::npos)
			final_text += last_char;
		if (!file.good() && chars.find(last_char) == std::wstring::npos)
			throw L"ERROR : File failed looking for characters : \"" + chars + L"\"\nString : " + final_text + L"\n";
		return final_text;
	}
	void seek_until(std::wifstream & file, const std::wstring & chars, wchar_t& last_char) {
		file.imbue(std::locale(file.getloc(), new std::codecvt_utf16<wchar_t, 0x10ffff, std::little_endian>()));
		while (file.good() && chars.find(last_char = get_with_ignore(file, L"#")) == std::wstring::npos) {}
		if (!file.good() && chars.find(last_char) == std::wstring::npos)
			throw L"ERROR : File failed looking for characters : \"" + chars + L"\"\n";
	}
	std::wstring search_until_exact(std::wifstream & file, const std::wstring & match) {
		std::wstring final_text;
		file.imbue(std::locale(file.getloc(), new std::codecvt_utf16<wchar_t, 0x10ffff, std::little_endian>()));
		while (file.good() && (match.size() <= final_text.size() ? (final_text.substr(final_text.size() - match.size()) != match) : true)) {
			final_text += get_with_ignore(file, L"#"); //Grabs until eof or found string
		}
		if (!file.good() && (match.size() <= final_text.size() ? final_text.substr(final_text.size() - match.size()) != match : true))
			throw L"ERROR : File failed looking for string : \"" + match + L"\"\nString : " + final_text + L"\n";
		return final_text.substr(0, final_text.size() - match.size());
	}
	void seek_until_exact(std::wifstream & file, std::wstring match) {
		std::wstring final_text;
		file.imbue(std::locale(file.getloc(), new std::codecvt_utf16<wchar_t, 0x10ffff, std::little_endian>()));
		while (file.good() && (match.size() <= final_text.size() ? (final_text.substr(final_text.size() - match.size()) != match) : true)) {
			final_text += get_with_ignore(file, L"#"); //Grabs until eof or found string
		}
		if (!file.good() && (match.size() <= final_text.size() ? final_text.substr(final_text.size() - match.size()) != match : true))
			throw L"ERROR : File failed looking for string : \"" + match + L"\"\nString : " + final_text + L"\n";
	}
	std::wstring search_until_exact(std::wifstream & file, const std::initializer_list<std::wstring> & match_list, std::wstring & last_match) {
		std::wstring final_text;
		auto match_func = [&](const std::wstring & match) { return match.size() <= final_text.size() ? (final_text.substr(final_text.size() - match.size()) == match) : false; };
		file.imbue(std::locale(file.getloc(), new std::codecvt_utf16<wchar_t, 0x10ffff, std::little_endian>()));
		while (file.good() && std::find_if(match_list.begin(), match_list.end(), match_func) == match_list.end()) {
			final_text += get_with_ignore(file, L"#"); //Grabs until eof or found string
		}
		auto match = std::find_if(match_list.begin(), match_list.end(), match_func);
		if (!file.good() && match == match_list.end())
			throw L"ERROR : File failed looking for strings in match_list\nString : " + final_text + L"\n";
		return final_text.substr(0, final_text.size() - match->size());
	}
	void seek_until_exact(std::wifstream & file, const std::initializer_list<std::wstring> & match_list, std::wstring & last_match) {
		std::wstring final_text;
		auto match_func = [&](const std::wstring & match) { return match.size() <= final_text.size() ? (final_text.substr(final_text.size() - match.size()) == match) : false; };
		file.imbue(std::locale(file.getloc(), new std::codecvt_utf16<wchar_t, 0x10ffff, std::little_endian>()));
		while (file.good() && std::find_if(match_list.begin(), match_list.end(), match_func) == match_list.end()) {
			final_text += get_with_ignore(file, L"#"); //Grabs until eof or found string
		}
		auto match = std::find_if(match_list.begin(), match_list.end(), match_func);
		if (!file.good() && match == match_list.end())
			throw L"ERROR : File failed looking for strings in match_list\nString : " + final_text + L"\n";
	}
	std::wstring load_quotes(std::wifstream & file, wchar_t& last_char) { //Locates and reads in everything between quotes
		seek_until(file, L"\"", last_char);
		return search_until(file, L"\"", last_char);
	};
}