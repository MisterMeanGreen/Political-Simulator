#pragma once
#include "map.h"
#include "person.h"
#include <string>
#include <atomic>

namespace pol_sim {
	class clique
	{

		static size_t pub_clique_id;

		//Vectors relating to state
		std::vector<state*> controlled_land;
		std::vector<person*> internal_people;

		//Stats relating to state
		int leader_id;
		const size_t clique_id;
		std::wstring name;
	public:
		//Constructor
		clique(std::wstring n, int l_id);
		~clique();

		//Get
		size_t get_id();
		std::wstring get_name();

		//Land
		size_t add_land(state* s); //Adds a state, return previous owner (or itself if no previous owner)
		bool remove_land(state* s); //Remove a state, returns true if removed state, returns false if it cannot find a state
	};
}