// Political Simulator.cpp : Defines the entry point for the console application.
//Nicholas Dundas
//Game about controlling the USA
//4/29/2018
#include <iostream>
#include "map.h"
#include "person.h"
#include "unicode.h"
using namespace std;


int main()
{
	init_locale();
	map USA;
	USA.load_map_files();
	person::load_player_files();
	wcout << L"\n" << USA.display;
	for (auto state : USA.states) {
		USA.render_state(state.name,L'A',0x0F);
	}
	person test(50,1000);
	person test_2(50, 1000);
	person test_3(50, 1000);
}

