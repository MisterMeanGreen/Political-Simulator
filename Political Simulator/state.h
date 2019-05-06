#pragma once
#include <vector>
#include <string>
#include <Windows.h>



namespace pol_sim {
	class clique;

	class state { //Represents each internal province within the map
		int population;
		int income;
		size_t clique_id; //current clique id controlling it
		std::vector<std::wstring> neighbors; //neighboring states
		std::wstring name; //name of state
		std::vector<COORD> pixels; //pixels on console

		clique* my_clique;
	public:
		enum {
			null = -1
		};

		//Constructor
		state(int p_id, std::wstring p_name, std::vector<std::wstring> p_neighbors, std::vector<COORD> p_pixels);
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
		size_t get_clique_id();
		clique* get_my_clique();

		//Set
		size_t set_clique_id(size_t id);
		std::wstring set_name(std::wstring new_name); //returns name
		void set_my_clique(clique* c);
	};
}