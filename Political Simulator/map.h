#pragma once
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <Windows.h>
#include <atomic>

#include "load.h"
#include "cursor.h"
#include "state.h"
namespace pol_sim {
	class map {
		//Used to indicate when state_at fails
		static state nullstate;

		//Where states are stored
		std::vector<state> states;
		std::wstring display;

		//Loading in map_files
		state load_state(std::wifstream& file, wchar_t& last_char); //Load a singular state from a file
		void load_map_files(std::wifstream& file); //Loads in the map_display and the states information within the map
	public:

		//Constructors
		map(std::wifstream& file);
		map(std::wstring file_name);
		~map();

		//Resets and creates new map
		void operator()(std::wifstream& file); //Reset the map with a new file
		void operator()(std::wstring& file_name); //Reset the map with a new file

		//Rendering
		void render_state(std::wstring wstr, wchar_t chr, WORD color); //Render a Single State from the Map
		std::wstring get_display();

		//Getting specific state
		state& state_at(COORD crd); //Returns state that contains the coordinate crd otherwise returns "NULL"
		state& operator[](size_t pos); //Returns state at pos
	};
}
