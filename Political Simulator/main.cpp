// Political Simulator.cpp : Defines the entry point for the console application.
//Nicholas Dundas
//Game about controlling the USA
//4/29/2018
#include <iostream>
#include <conio.h>
#include "map.h"
#include "person.h"
#include "unicode.h"
#include "cursor.h"

using namespace std;


int main()
{
	init_locale();
	map USA;
	USA.load_map_files();
	person::load_player_files();
	wcout << L"\n" << USA.display;
	for (auto state : USA.states) {
		USA.render_state(state.name,L'A',0xFF);
	}
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

