#pragma once
#include <vector>
#include <string>
#include <Windows.h>

class state {
	int population;
	int income;
	int clique_id; //current clique id controlling it
	std::vector<std::wstring> neighbors; //neighboring states
	std::wstring name; //name of state
	std::vector<COORD> pixels; //pixels on console
public:
	//Constructor
	state(int p_id, std::wstring p_name,std::vector<std::wstring> p_neighbors,std::vector<COORD> p_pixels);
	state(); //used for null
	~state();

	//Neighbor Functions
	bool is_neighbor(std::wstring p_neighbor);  //Returns true if neighbor
	bool is_neighbor(state p_neighbor); //Returns true if neighbor

	//Postional Functions
	COORD avg_coord(); //Calculates the average coordinates of the state

	//Get
	const std::vector<COORD>& get_pixels();
	std::wstring get_name(); //returns name
};
