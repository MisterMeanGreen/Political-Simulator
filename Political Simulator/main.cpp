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

