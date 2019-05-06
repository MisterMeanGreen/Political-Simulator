#pragma once
//WINDOWS API
#include <Windows.h>

//WCOUT
#include <iostream>

//BOUNDS
#include <algorithm>

//TO_WSTRING
#include <string>
namespace pol_sim {
	class cursor
	{
		//Current
		COORD curr_pos; //Stores the current position
		WORD color;
		wchar_t curr_char; //Stores the current character

		//Previous drawn Coord
		wchar_t last_char; //Stores last character
		wchar_t last_color; //Stores last color

		//Used for Windows API functions
		static HANDLE hConsole;
		static DWORD num_read;

		//Bounds
		COORD lower_B;
		COORD upper_B;
	public:
		//Constructors
		cursor();
		cursor(COORD pos);
		cursor(wchar_t chr);
		cursor(COORD pos, wchar_t chr);
		cursor(COORD pos, wchar_t chr, WORD clr);
		~cursor();

		//Moves cursor
		void move_to(COORD pos); //Sets position and redraws mouse

		//Draw
		void redraw();

		//Postional Primitives
		COORD get_pos(); //gets current position
		void set_pos(COORD pos); //Sets position

		//Character and Color
		void set_char(wchar_t chr); //sets charcters to be printed
		void set_attr(WORD chr);

		//Drawing Primitives
		void clear(); //clears where the character is stored
		void draw(); //draws the character at curr_pos
		WORD get_char(); //gets characters

		//API Cursor Controls
		static void set_cur_color(WORD color);
		static void set_cur_pos(COORD crd); //sets raw_cursor to crd

		//API Console Read
		static wchar_t get_cur_char(COORD crd); //gets character at crd
		static WORD get_cur_charinfo(COORD crd); //gets character info at crd

		//Get Bounds
		COORD get_l_bound();
		COORD get_h_bound();

		//Set Bounds
		void set_bounds(COORD lower, COORD upper);
	};
}
