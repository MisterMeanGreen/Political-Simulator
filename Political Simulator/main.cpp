// Political Simulator.cpp : Defines the entry point for the console application.
//Nicholas Dundas
//Game about controlling the USA
//4/29/2018

//cout
#include <iostream>

//_getch
#include <conio.h>
#include "map.h"
#include "person.h"
#include "unicode.h"
#include "cursor.h"
#include "clique.h"
#include <random>

using namespace std;

int main()
{

	init_locale();
	map USA(L"USA.txt");
	person::load_player_files();
	person test(50, 2000);
	wcout << L"\n" << USA.get_display();
	cursor cur({ 0,0 },L'X',0x0f);
	while (true) {
		int key_press = _getch();
		switch (key_press) {
		case 72: //UP
			cur.move_to({ cur.get_pos().X,cur.get_pos().Y - 1 });
			break;
		case 80: //DOWN
			cur.move_to({ cur.get_pos().X,cur.get_pos().Y + 1 });
			break;
		case 75: //LEFT
			cur.move_to({ cur.get_pos().X - 1,cur.get_pos().Y });
			break;
		case 77: //RIGHT
			cur.move_to({ cur.get_pos().X + 1,cur.get_pos().Y });
			break;
		}
	}
	
}

