#pragma once
#include <vector>
#include <string>
#include <Windows.h>



namespace pol_sim {
	class clique;

	class state { //Represents each internal province within the map
		int population;
		int income;
		std::vector<std::wstring> neighbors; //neighboring states
		std::wstring name; //name of state
		std::vector<COORD> pixels; //pixels on console

		clique* my_clique;
	public:
		enum {
			null = 4294967295
		};

		//Constructor
		state(std::wstring p_name, std::vector<std::wstring> p_neighbors, std::vector<COORD> p_pixels, int p_inc, int p_pop, clique* c_ptr);
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
		clique* get_my_clique();

		//Set
		std::wstring set_name(std::wstring new_name); //returns name
		void set_my_clique(clique* c);
	};
}