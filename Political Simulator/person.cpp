#include "person.h"
namespace pol_sim {
	std::vector<effect>  person::traits_list;
	std::vector<std::wstring> person::m_names;
	std::vector<std::wstring> person::f_names;
	std::vector<std::wstring> person::l_names;
	std::random_device person::rand_dev;
	std::default_random_engine person::gen(rand_dev());
	std::uniform_int_distribution<int> person::dist(0, 99);
	void person::raw_add(effect trait) {
		traits.push_back(trait);
		add_stat(effect::stat_ids::diplomacy, traits.back().get_stat(effect::stat_ids::diplomacy));
		add_stat(effect::stat_ids::intrigue, traits.back().get_stat(effect::stat_ids::intrigue));
		add_stat(effect::stat_ids::appeal, traits.back().get_stat(effect::stat_ids::appeal));
		add_stat(effect::stat_ids::command, traits.back().get_stat(effect::stat_ids::command));
	}
	bool person::remove_trait(uint16_t trait_num) {//Removes a Single Trait at Postion X
		if (trait_num < traits.size() - 1) {
			add_stat(effect::stat_ids::diplomacy, -traits.back().get_stat(effect::stat_ids::diplomacy));
			add_stat(effect::stat_ids::intrigue, -traits.back().get_stat(effect::stat_ids::intrigue));
			add_stat(effect::stat_ids::appeal, -traits.back().get_stat(effect::stat_ids::appeal));
			add_stat(effect::stat_ids::command, -traits.back().get_stat(effect::stat_ids::command));
			traits.erase(traits.begin() + trait_num);
			return true;
		}
		else return false;
	}
	bool person::remove_trait(std::wstring name) { //Remove trait via name
		auto trait_itt = traits.begin();
		uint16_t trait_num = 0;
		while (trait_itt->name != name && trait_num < (traits.size() - 1)) {
			trait_itt++;
			trait_num++;
		}
		return remove_trait(trait_num);
	}
	bool person::remove_trait(effect trait) { //Remove trait via another trait
		return remove_trait(trait.name);
	}
	bool person::add_trait_no_remove(effect trait) { //Add a single trait
		for (auto curr_trait : traits) {
			for (auto my_neg_trait : trait.negative_traits) {
				if (curr_trait.name == my_neg_trait) {
					remove_trait(curr_trait);
					return false;
				}
			}
			if (curr_trait == trait) {
				remove_trait(curr_trait);
				return false;
			}
			for (auto neg_trait : curr_trait.negative_traits) {
				if (neg_trait == trait.name) {
					remove_trait(neg_trait);
					return false;
				}
			}
		}
		raw_add(trait);
		return true;
	}
	bool person::add_trait(effect trait) { //Add a single trait
		for (auto curr_trait : traits) {
			for (auto my_neg_trait : trait.negative_traits) {
				if (curr_trait.name == my_neg_trait) return false;
			}
			if (curr_trait == trait) return false;
			for (auto neg_trait : curr_trait.negative_traits) {
				if (neg_trait == trait.name) return false;
			}
		}
		raw_add(trait);
		return true;
	}
	void person::generate_random_traits() {//Generates Randomized Traits
		std::uniform_int_distribution<int> rand(-4, 4);
		std::uniform_int_distribution<int> rand_trait_num(0, traits_list.size() - 1);
		for (int x = 0; x < (static_cast<int>(age) / 10) + rand(gen); x++) {
			while (!add_trait_no_remove(traits_list[rand_trait_num(gen)]));
		}
	}
	void person::generate_random_stats() {
		std::uniform_int_distribution<int> rand_stat(0, 3); //Random stat to upgrade
		std::uniform_int_distribution<int> rand_total(0, (age / 2) + 10); //Random total amount you can upgrade
		auto total = rand_total(gen);
		for (auto x = 0; x < total; x++)
			stats[gen() % 4]++;
	}
	template<typename T>
	T person::get_random_item(std::vector<T> list) {
		return list[gen() % list.size()];
	}
	void person::clear_traits() {
		while (!traits.empty()) remove_trait(traits.back());
	}
	int person::add_stat(size_t stat, int amount) { //Change a one of the stats by amount
		return stats[stat] += amount;
	}
	int person::get_stat(size_t stat) {
		return stats[stat];
	}
	int person::set_stat(size_t stat, int amount)
	{
		return stats[stat] = amount;
	}
	uint32_t person::pub_id;
	std::wstring person::get_first_name() { return first_name; }
	std::wstring person::get_last_name() { return last_name; }
	std::wstring person::get_name() { return get_first_name() + L' ' + get_last_name(); }
	int person::add_money(int amount) { return money += amount; }
	int person::get_money() { return money; }
	int person::get_age() { return age; }
	uint32_t person::get_id() { return id; }
	bool person::get_gender() { return gender == male; }
	auto& person::operator[](uint32_t c) { return traits[c]; }
	person::person(std::wstring p_first_name, std::wstring p_last_name, uint32_t p_age, bool p_gender, int p_money, int p_diplomacy, int p_intrigue, int p_appeal, int p_command) : id(++pub_id) {
		stats.resize(effect::stat_ids::STAT_SIZE);
		first_name = p_first_name;
		last_name = p_last_name;
		age = p_age;
		gender = p_gender;
		money = p_money;
		stats[effect::stat_ids::diplomacy] = p_diplomacy;
		stats[effect::stat_ids::intrigue] = p_intrigue;
		stats[effect::stat_ids::appeal] = p_appeal;
		stats[effect::stat_ids::command] = p_command;
		generate_random_traits();
		generate_random_stats();
	}
	person::person(std::wstring p_first_name, std::wstring p_last_name, uint32_t p_age, bool p_gender, int p_money) : person(p_first_name, p_last_name, p_age, p_gender, p_money, 0, 0, 0, 0) {}
	person::person(uint32_t p_age, int p_money) : person(L"NULL", get_random_item(l_names), p_age, (dist(gen) < 90 ? male : female), p_money, 0, 0, 0, 0) {
		if (gender == male)
			first_name = get_random_item(m_names);
		else
			first_name = get_random_item(f_names);
	}
	void person::load_player_files() { //Loads traits file, names for both females and males, and the last names
		std::wifstream file(L"traits.txt");
		std::wstring current_text;
		wchar_t last_char;
		auto load_until = [&](std::wstring chars) { return search_until(file, chars, last_char); };
		auto load_string = [&]() { return load_quotes(file, last_char); };
		try { //Attempt to load traits
			load_until(L"T");
			load_until(L"{");
			while (last_char != L'}') { //Load traits
				traits_list.push_back(person::load_trait(file, last_char));
			}
		}
		catch (std::wstring error_recieved) {
			throw L"ERROR : Failed to load Traits file\n" + error_recieved;
		}
		file.close();
		file.open("names.txt"); //Load names
		try {
			load_until(L"M");
			load_until(L"{");
			do {
				m_names.push_back(load_until(L",}"));
			} while (last_char != '}');
		}
		catch (std::wstring error_recieved) {
			throw L"ERROR : Failed to load male names\n" + error_recieved;
		}
		try {
			load_until(L"F");
			load_until(L"{");
			do {
				f_names.push_back(load_until(L",}"));
			} while (last_char != '}');
		}
		catch (std::wstring error_recieved) {
			throw L"ERROR : Failed to load female names\n" + error_recieved;
		}
		try {
			load_until(L"L");
			load_until(L"{");
			do {
				l_names.push_back(load_until(L",}"));
			} while (last_char != '}');
		}
		catch (std::wstring error_recieved) {
			throw L"ERROR : Failed to load last names\n" + error_recieved;
		}
	}
	effect person::load_trait(std::wifstream& file, wchar_t& last_char) { //Loads trait from file
		effect temp_effect;
		std::vector<std::wstring> effect_stat_id_names({ L"Diplomacy",L"Intrigue",L"Appeal",L"Command" });
		try {
			std::wstring current_text; //Text currently read
			auto load_until = [&](std::wstring chars) { return search_until(file, chars, last_char); };
			auto load_string = [&]() { return load_quotes(file, last_char); };
			temp_effect.name = load_string();
			load_until(L",");
			temp_effect.description = load_string();
			load_until(L",");
			for (size_t current_stat_id = 0; current_stat_id < 4; current_stat_id++) {
				try {
					current_text = load_until(L",");
					temp_effect.set_stat(current_stat_id, stoi(current_text));
				}
				catch (...) {
					throw L"ERROR : Cannot Assign " + effect_stat_id_names[current_stat_id] + L"\n\"" + current_text + L"\" could not be assigned.";
				}
			}
			load_until(L"[");
			do {
				current_text = load_string();
				temp_effect.negative_traits.push_back(current_text);
				load_until(L",]");
			} while (last_char != ']');
			load_until(L",}");
		}
		catch (std::wstring error_recieved) {
			throw L"Failed to load trait\n" + error_recieved + L"\nName : L" + temp_effect.name + L"\nDesc : L" + temp_effect.description + L"\nDiplomacy : L" + std::to_wstring(temp_effect.get_stat(effect::stat_ids::diplomacy)) + L"\nIntrigue : L" + std::to_wstring(temp_effect.get_stat(effect::stat_ids::intrigue)) + L"\nAppeal : L" + std::to_wstring(temp_effect.get_stat(effect::stat_ids::appeal)) + L"\nCommand : L" + std::to_wstring(temp_effect.get_stat(effect::stat_ids::command));
		}
		return temp_effect;
	}
}