// Political Simulator.cpp : Defines the entry point for the console application.
//Nicholas Dundas
//Game about controlling the USA
//4/29/2018

//cout
#include <iostream>

//_getch
#include <conio.h>
#include "unicode.h"
#include "engine.h"
#include "cursor.h"
#include <random>

using namespace std;

int main()
{
	pol_sim::engine test(L"paths.txt");
	test.set_title(L"Political Simulator");
	pol_sim::clique s(L"Test", L'1', 0x0f);
	pol_sim::clique s_2(L"Test_2", L'2', 0x0f);
	wcout << L"\n" << test.game_map.get_display();
	s.add_land(test.game_map[0]);
	s.add_land(test.game_map[1]);
	s_2.add_land(test.game_map[2]);
	s_2.add_land(test.game_map[3]);
	s.render_clique();
	s_2.render_clique();
	pol_sim::cursor::set_cur_pos({ 0,0 });
	wcout << L"\n" << test.game_map.get_display();
	s.add_land(test.game_map[2]);
	s.render_clique();
	s_2.render_clique();
	pol_sim::cursor cur({ 0,0 },L'X',0x0f);
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

