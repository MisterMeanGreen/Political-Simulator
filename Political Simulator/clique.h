#pragma once
#include "map.h"
#include "person.h"
#include <string>
#include <atomic>


class clique
{
	static int pub_clique_id;
	std::vector<state*> controlled_land;
	std::vector<std::shared_ptr<person>> internal_people;
	int leader_id;
	int clique_id;
public:

	std::wstring name;
	clique(std::wstring n,int l_id);
	~clique();
	bool add_land(std::shared_ptr<state> s); //Adds a state, return true if it can add state;
	bool remove_land(std::shared_ptr<state> s); //Remove a state, returns true if removed state, returns false if it cannot find a state
};

