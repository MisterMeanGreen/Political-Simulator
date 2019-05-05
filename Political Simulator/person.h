#pragma once

//Used for functions
#include <string>
#include <vector>
#include <random>

//Used to help load functions
#include "load.h"

//Used for traits
#include "effect.h"

namespace pol_sim {
	class person {
		//Used for random number gen
		static std::random_device rand_dev;
		static std::default_random_engine gen;
		static std::uniform_int_distribution<int> dist;

		//Where information from files are stored
		static std::vector<effect>  traits_list;
		static std::vector<std::wstring> m_names;
		static std::vector<std::wstring> f_names;
		static std::vector<std::wstring> l_names;

		//ID
		static size_t pub_id;
		size_t id;
		size_t clique_id;

		//Stats of the person
		std::wstring first_name; //Usually Random
		std::wstring last_name; //Dynastys!
		size_t age; //Age
		bool gender; //Gender
		int money; //Moolah
		std::vector<effect> traits; //Traits affect stats and other things
		std::vector<int> stats; //Defines different stats

	public:
		//Defines gender values (STORED AS BOOL)
		enum genders
		{
			male = 0, female = 1
		};

		//Constructors
		person(std::wstring p_first_name, std::wstring p_last_name, size_t p_age, bool p_gender, int p_money, int p_diplomacy, int p_intrigue, int p_appeal, int p_command);
		person(std::wstring p_first_name, std::wstring p_last_name, size_t p_age, bool p_gender, int p_money);
		person(size_t p_age, int p_money);

		//Basic person functionality
		std::wstring get_first_name();
		std::wstring get_last_name();
		std::wstring get_name();
		int add_money(int amount);
		int get_money();
		int get_age();
		bool get_gender();
		size_t get_id();

		size_t set_clique_id(size_t c_id) {
			clique_id = c_id;
		}

		//Stat functionality
		int add_stat(size_t stat, int amount); //Change a one of the stats by amount	
		int get_stat(size_t stat); //Return stat as defined by enum
		int set_stat(size_t stat, int amount); //Set a stat to amount

		//Trait functionality
		auto& operator[](size_t c);
		bool remove_trait(uint16_t trait_num); //Removes a Single Trait at Postion X
		bool remove_trait(std::wstring name); //Remove trait via name
		bool remove_trait(effect trait); //Remove trait via another trait
		bool add_trait_no_remove(effect trait); //Add a single trait
		bool add_trait(effect trait); //Add a single trait
		void clear_traits();

		//Generates Randomized Traits
		void generate_random_traits();
		void generate_random_stats();
		template<typename T>
		T get_random_item(std::vector<T> list);

		//Loading Files
		static void load_player_files(); //Loads traits file, names for both females and males, and the last names
		static effect load_trait(std::wifstream& file, wchar_t& last_char); //Loads traits from file
	private:
		void raw_add(effect trait);
	};
}