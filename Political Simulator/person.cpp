#include "person.h"
#include "clique.h"
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
		add_stat(effect::stat_ids::diplomacy, traits.back().get_stat(L"diplomacy"));
		add_stat(effect::stat_ids::intrigue, traits.back().get_stat(L"intrigue"));
		add_stat(effect::stat_ids::appeal, traits.back().get_stat(L"appeal"));
		add_stat(effect::stat_ids::command, traits.back().get_stat(L"command"));
	}
	bool person::remove_trait(uint16_t trait_num) {//Removes a Single Trait at Postion X
		if (trait_num < traits.size() - 1) {
			add_stat(effect::stat_ids::diplomacy, -traits.back().get_stat(L"diplomacy"));
			add_stat(effect::stat_ids::intrigue, -traits.back().get_stat(L"intrigue"));
			add_stat(effect::stat_ids::appeal, -traits.back().get_stat(L"appeal"));
			add_stat(effect::stat_ids::command, -traits.back().get_stat(L"command"));
			traits.erase(traits.begin() + trait_num);
			return true;
		}
		else return false;
	}
	bool person::remove_trait(std::wstring name) { //Remove trait via name
		auto trait_itt = traits.begin();
		uint16_t trait_num = 0;
		while (trait_itt->get_name() != name && trait_num < (traits.size() - 1)) {
			trait_itt++;
			trait_num++;
		}
		return remove_trait(trait_num);
	}
	bool person::remove_trait(effect trait) { //Remove trait via another trait
		return remove_trait(trait.get_name());
	}
	bool person::add_trait_no_remove(effect trait) { //Add a single trait
		for (auto curr_trait : traits) {
			for (auto my_neg_trait : trait.negative_traits) {
				if (curr_trait.get_name() == my_neg_trait) {
					remove_trait(curr_trait);
					return false;
				}
			}
			if (curr_trait == trait) {
				remove_trait(curr_trait);
				return false;
			}
			for (auto neg_trait : curr_trait.negative_traits) {
				if (neg_trait == trait.get_name()) {
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
				if (curr_trait.get_name() == my_neg_trait) return false;
			}
			if (curr_trait == trait) return false;
			for (auto neg_trait : curr_trait.negative_traits) {
				if (neg_trait == trait.get_name()) return false;
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
	clique* person::set_my_clique(clique* c)
	{
		return my_clique = c;
	}
	clique* person::get_my_clique()
	{
		return my_clique;
	}
	size_t person::set_my_clique_id(size_t _id)
	{
		return my_clique_id = _id;
	}
	size_t person::get_my_clique_id()
	{
		return my_clique_id;
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
	size_t person::pub_id;
	std::wstring person::get_first_name() { return first_name; }
	std::wstring person::get_last_name() { return last_name; }
	std::wstring person::get_name() { return get_first_name() + L' ' + get_last_name(); }
	int person::add_money(int amount) { return money += amount; }
	int person::get_money() { return money; }
	int person::get_age() { return age; }
	size_t person::get_id() { return id; }
	bool person::get_gender() { return gender == male; }
	auto person::operator[](size_t c) { return traits[c]; }
	person::person(std::wstring p_first_name, std::wstring p_last_name, size_t p_age, bool p_gender, int p_money, int p_diplomacy, int p_intrigue, int p_appeal, int p_command, clique* c) : id(++pub_id) {
		my_clique = c;
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
	person::person(std::wstring p_first_name, std::wstring p_last_name, size_t p_age, bool p_gender, int p_money, clique* c) : person(p_first_name, p_last_name, p_age, p_gender, p_money, 0, 0, 0, 0, c) {}
	person::person(size_t p_age, int p_money, clique* c) : person(L"NULL", get_random_item(l_names), p_age, (dist(gen) < 90 ? male : female), p_money, 0, 0, 0, 0,c) {
		if (gender == male)
			first_name = get_random_item(m_names);
		else
			first_name = get_random_item(f_names);
	}
	person::~person()
	{
		my_clique->remove_person(this);
	}
	void person::load_player_files(std::wstring trait_name, std::wstring names_list) {
		std::wifstream file(trait_name, std::ios::binary);
		wchar_t last_char;
		std::wstring last_text;
		auto seek = [&](const std::wstring & chrs) { return seek_until(file, chrs, last_char); };
		auto load_until = [&](std::wstring chars) { return search_until(file, chars, last_char); };
		auto search_quotes = [&]() { return load_quotes(file, last_char); };
		try {
			seek(L"{;");
			while (last_char != L';') { //Simple shitty file reader REDO AT SOMEPOINT
				std::wstring current_text;
				std::wstring name;
				std::wstring description;
				std::map<std::wstring, int> effect_attributes;
				std::vector<std::wstring> effect_negative_traits;
				if (search_quotes() == L"name") {
					seek(L"=");
					name = search_quotes();
					seek(L",");
				}
				if (search_quotes() == L"description") {
					seek(L"=");
					description = search_quotes();
					seek(L",");
				}
				while ((current_text = search_quotes()) != L"end") { //Load attributes
					seek(L"=");
					if (current_text != L"negative_traits") {
						ignore_white_space(file);
						effect_attributes[current_text] = stoi(search_until(file, L",", last_char));
					}
					else {
						seek(L"{");
						while (last_char != L'}') {
							effect_negative_traits.push_back(search_quotes());
							seek(L",}");
						}
					}
				}
				seek(L"}");
				person::traits_list.push_back(effect(name, description, effect_attributes, effect_negative_traits));
				seek(L",;");
				if (last_char == L',')
					seek(L"{");
			}
		}
		catch (std::wstring error_recieved) {
			throw L"ERROR : Failed to load traits\n" + error_recieved;
		}
		file.close();
		file.open(names_list, std::ios::binary); //Load names
		try {
			seek(L"M");
			seek(L"{");
			do {
				m_names.push_back(load_until(L",}"));
			} while (last_char != '}');
		}
		catch (std::wstring error_recieved) {
			throw L"ERROR : Failed to load male names\n" + error_recieved;
		}
		try {
			seek(L"F");
			seek(L"{");
			do {
				f_names.push_back(load_until(L",}"));
			} while (last_char != '}');
		}
		catch (std::wstring error_recieved) {
			throw L"ERROR : Failed to load female names\n" + error_recieved;
		}
		try {
			seek(L"L");
			seek(L"{");
			do {
				l_names.push_back(load_until(L",}"));
			} while (last_char != '}');
		}
		catch (std::wstring error_recieved) {
			throw L"ERROR : Failed to load last names\n" + error_recieved;
		}
	}
}