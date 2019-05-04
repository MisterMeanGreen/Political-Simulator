#pragma once
#include <string>
#include <iostream>
#include <vector>
class effect { //Used as traits
	std::vector<int> stat_effects; //Stores info relating to changing a characters stats
public:
	enum stat_ids {
		diplomacy = 0, //Ability for Person to work with other Politicians
		intrigue, //Ability for Person to conduct spying and espioange
		appeal,   //Ability for person to appeal to the people
		command,  //Ability for Person to control others and command armies
		opinion_general,
		STAT_SIZE
	};
	//Constructors
	effect(std::wstring p_name, std::wstring p_desc, int p_diplo, int p_int, int p_app, int p_comm);
	effect();
	~effect();

	//Get stat_effects
	int get_stat(size_t stat);
	int set_stat(size_t stat, int amount);

	//Stores basic info
	std::wstring name;
	std::wstring description;
	std::vector<std::wstring> negative_traits; //Defines traits that the current trait cannot be in conjunction with

	bool operator==(effect x);
	bool operator!=(effect x);
	bool contains_ntrait(std::wstring s);
};
//To print out an effect
std::wostream &operator<<(std::wostream& os, effect const &temp_effect);

