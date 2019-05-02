#pragma once
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <Windows.h>

#include "helper.h"
#include "cursor.h"
class map {
public:
private:
	class state {
	public:
		int population;
		int income;
		std::vector<std::wstring> neighbors; //neighboring states
		std::vector<COORD> pixels; //pixels on console
		int clique_id; //current clique id controlling it
		std::wstring name; //name of state
		state(int p_id, std::wstring p_name);
		state(int p_id);
		~state();
		const auto& get_neighbors();
		COORD avg_coord(); //Calculates the average coordinates of the state
	};
	state load_state(std::wifstream& file, wchar_t& last_char); //Load a singular state from a file


public:
	std::wstring display;
	std::vector<state> states;
	void load_map_files(); //Loads in the map_display and the states information within the map
	void render_state(std::wstring wstr, wchar_t chr, WORD color); //Render a Single State from the Map
};

