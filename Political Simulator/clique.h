#pragma once
#include "map.h"
#include "person.h"
#include <string>
#include <atomic>


namespace pol_sim {
	class clique
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
		DWORD color;
	public:
		//Constructor
		clique(std::wstring n, wchar_t s, DWORD c);
		~clique();

		//Get
		size_t get_id();
		std::wstring get_name();

		//Render
		void render_clique();

		//TODO PEOPLE

		//Land
		size_t add_land(state* s); //Adds a state, return previous owner (or itself if no previous owner)
		bool remove_land(state* s); //Remove a state, returns true if removed state, returns false if it cannot find a state
	};
}