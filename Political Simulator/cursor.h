#pragma once
//WINDOWS API
#include <Windows.h>

//WCOUT
#include <iostream>

class cursor
{
	COORD curr_pos; //Stores the current position
	WORD color;
	wchar_t curr_char; //Stores the current character
	wchar_t last_char; //Stores last character
	wchar_t last_color; //Stores last color
	static HANDLE hConsole;
	static DWORD num_read;
public:
	cursor();
	cursor(COORD pos);
	cursor(wchar_t chr);
	cursor(COORD pos,wchar_t chr);
	cursor(COORD pos, wchar_t chr, WORD clr);
	~cursor();
	void move_to(COORD pos); //Sets position and redraws mouse
	COORD get_pos(); //gets current position
	void set_pos(COORD pos); //Sets position
	void set_char(wchar_t chr); //sets charcters to be printed
	void set_attr(WORD chr);
	void clear(); //clears where the character is stored
	void draw(); //draws the character at curr_pos
	WORD get_char(); //gets characters
	static void set_cur_color(WORD color);
	static void set_cur_pos(COORD crd); //sets raw_cursor to crd
	static wchar_t get_cur_char(COORD crd); //gets character at crd
	static WORD get_cur_charinfo(COORD crd); //gets character info at crd
};

