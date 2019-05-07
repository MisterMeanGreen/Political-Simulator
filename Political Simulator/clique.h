#pragma once
#include "map.h"
#include "person.h"
#include <string>
#include <vector>

namespace pol_sim {
	class clique //Represents Nations within the Game
	{
		//Used to keep track of new creation of cliques
		static size_t pub_clique_id;

		//Land Controlled
		std::vector<state*> controlled_land;

		//People within the state
		std::vector<person*> internal_people;

		//Stats relating to state
		int leader_id; 
		const size_t clique_id;
		std::wstring name;

		wchar_t symbol;
		WORD color;
	public:
		//Constructor
		clique(std::wstring n, wchar_t s, WORD c);
		~clique();

		//Get
		size_t get_id();
		std::wstring get_name();

		//Render
		void render_clique();

		//People
		clique* transfer_person(person* p); //Returns previous owner
		bool remove_person(person* p); //Remove a person, returns true if removed a person, returns false if it cannot find a person

		//Land
		clique* add_land(state* s); //Adds a state, return previous owner (or itself if no previous owner)
		bool remove_land(state* s); //Remove a state, returns true if removed state, returns false if it cannot find a state
	};
}