#pragma once
#include <string>
#include <iostream>
#include <vector>
class effect { //Used as traits
public:
	std::wstring name;
	std::wstring description;
	int diplomacy; //Ability for Person to work with other Politicians
	int intrigue; //Ability for Person to conduct spying and espioange
	int appeal; //Ability for person to appeal to the people
	int command; //Ability for Person to control others
	effect(std::wstring p_name, std::wstring p_desc, int p_diplo, int p_int, int p_app, int p_comm);
	std::vector<std::wstring> negative_traits; //Defines traits that the current trait cannot be in conjunction with
	effect();
	~effect();
	bool operator==(effect x);
	bool operator!=(effect x);
	bool contains_ntrait(std::wstring s);
};
std::wostream &operator<<(std::wostream& os, effect const &temp_effect);

