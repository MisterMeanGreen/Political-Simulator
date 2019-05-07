#pragma once
//Functions that are called in multiple class files
#include "load.h"
namespace pol_sim {
	std::wstring search_until(std::wifstream& file, std::wstring chars, wchar_t& last_char) {
		std::wstring final_text;
		file.imbue(std::locale(file.getloc(), new std::codecvt_utf16<wchar_t, 0x10ffff, std::little_endian>()));
		while (file.good() && chars.find(last_char = file.get()) == std::wstring::npos)
			final_text += last_char;
		if (!file.good()) 
			throw L"ERROR : File failed looking for characters : \"" + chars + L"\"\nString : " + final_text + L"\n";
		return final_text;
	}
	void seek_until(std::wifstream& file, std::wstring chars, wchar_t& last_char) {
		file.imbue(std::locale(file.getloc(), new std::codecvt_utf16<wchar_t, 0x10ffff, std::little_endian>()));
		while (file.good() && chars.find(last_char = file.get()) == std::wstring::npos)
		if (!file.good())
			throw L"ERROR : File failed looking for characters : \"" + chars + L"\"\n";
	}
	std::wstring search_until_exact(std::wifstream& file, std::wstring match) {
		std::wstring final_text;
		file.imbue(std::locale(file.getloc(), new std::codecvt_utf16<wchar_t, 0x10ffff, std::little_endian>()));
		for (size_t pos = 0; pos < match.size() && file.good(); pos++) 
			final_text += file.get(); //Grabs the intial characters
		while (file.good() && final_text.substr(final_text.size() - match.size()) != match)
			final_text += file.get(); //Grabs until eof or found string
		if(!file.good())
			throw L"ERROR : File failed looking for string : \"" + match + L"\"\nString : " + final_text + L"\n";
		return final_text;
	}
	void seek_until_exact(std::wifstream& file, std::wstring match) {
		std::wstring final_text;
		file.imbue(std::locale(file.getloc(), new std::codecvt_utf16<wchar_t, 0x10ffff, std::little_endian>()));
		for (size_t pos = 0; pos < match.size() && file.good(); pos++)
			final_text += file.get(); //Grabs the intial characters
		while (file.good() && final_text.substr(final_text.size() - match.size()) != match)
			final_text += file.get(); //Grabs until eof or found string
		if (!file.good())
			throw L"ERROR : File failed looking for string : \"" + match + L"\"\nString : " + final_text + L"\n";
	}
	std::wstring load_quotes(std::wifstream& file, wchar_t& last_char) { //Locates and reads in everything between quotes
		seek_until(file, L"\"", last_char);
		return search_until(file, L"\"", last_char);
	};
}