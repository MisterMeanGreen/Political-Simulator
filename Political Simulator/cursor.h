#pragma once
#include <Windows.h>
#include <iostream>
#include "helper.h"
class cursor
{
	COORD curr_pos; //Stores the current position
	WORD color;
	wchar_t curr_char; //Stores the current character
	wchar_t last_char; //Stores last character
	wchar_t last_color; //Stores last color
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
};

