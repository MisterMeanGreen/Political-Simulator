// Political Simulator.cpp : Defines the entry point for the console application.
//Nicholas Dundas
//Game about controlling the USA
//4/29/2018
#include <iostream>
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
	cursor test({ 6,9 }, L'X');
	test.move_to({ 10,16 });
}

