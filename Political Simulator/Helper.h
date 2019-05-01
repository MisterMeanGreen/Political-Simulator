#pragma once
#include <string>
#include <fstream>
#include <iostream>
#include <Windows.h>

wchar_t wget(std::wifstream& file);
std::wstring search_until(std::wifstream& file, std::wstring chars, wchar_t& last_char);
std::wstring load_quotes(std::wifstream& file, wchar_t& last_char); //Locates and reads in everything between quotes
void set_color(WORD color);
void set_pos(COORD crd); //sets raw_cursor to crd
wchar_t get_char(COORD crd); //gets character at crd
WORD get_charinfo(COORD crd); //gets character info at crd