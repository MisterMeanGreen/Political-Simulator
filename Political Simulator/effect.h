#pragma once

#include <string>
#include <iostream>
#include <map>
#include <vector>
#include <array>

namespace pol_sim {
class effect {
	std::wstring name;
	std::wstring description;
	std::map<std::wstring, int> stat_effects; //Stores info relating to changing a characters stats
public:
	std::vector<std::wstring> negative_traits; //Defines traits that the current trait cannot be in conjunction with
	enum stat_ids {
		diplomacy = 0, //Ability for Person to work with other Politicians
		intrigue, //Ability for Person to conduct spying and espioange
		appeal,   //Ability for person to appeal to the people
		command,  //Ability for Person to control others and command armies
		opinion_general,
		STAT_SIZE
	};
		const static std::array<std::wstring, 4> effect_stat_id_names;
		//Constructors
		effect(const std::wstring& p_name, const std::wstring& p_desc, const std::map<std::wstring, int>& p_effects, const std::vector<std::wstring>& p_negative_traits);
		//Get stat_effects
		int get_stat(std::wstring stat);
		std::wstring get_name();
		std::wstring get_description();

		int set_stat(std::wstring stat, int amount);


		//Comparison
		bool operator==(effect x);
		bool operator!=(effect x);
		bool contains_ntrait(std::wstring s);
	};
}