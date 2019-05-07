#include "clique.h"

namespace pol_sim {
	size_t clique::pub_clique_id = 0;
	clique::clique(std::wstring n, wchar_t s, WORD c) : clique_id(++pub_clique_id)
	{
		symbol = s;
		color = c;
		leader_id = 0;
		name = n;
	}
	clique::~clique()
	{
		for (auto s : controlled_land)
			remove_land(s);
	}
	size_t clique::get_id()
	{
		return clique_id;
	}
	std::wstring clique::get_name()
	{
		return name;
	}
	void clique::render_clique()
	{
		for (auto s : controlled_land)
			map::render_state(*s,symbol,color);
	}
	clique* clique::transfer_person(person* p)
	{
		for (auto i_p : internal_people)
			if (p == i_p)
				return this;
		clique* temp = p->get_my_clique();
		p->get_my_clique()->remove_person(p);
		p->set_my_clique(this);
		p->set_my_clique_id(clique_id);
		internal_people.push_back(p);
		return temp;
	}
	bool clique::remove_person(person* p)
	{
		for (auto ptr = internal_people.begin(); ptr < internal_people.end(); ptr++) {
				if (*ptr == p) {
					p->set_my_clique(nullptr);
					p->set_my_clique_id(state::null);
					internal_people.erase(ptr);
					return true;
				}
			}
		return false;
	}
	clique* clique::add_land(state* s)
	{
		if (std::find_if(controlled_land.begin(), controlled_land.end(), [&](state * c) {return c == s; }) != controlled_land.end())
			return this;
		clique* temp = s->get_my_clique();
		if(s->get_my_clique() != nullptr)
			s->get_my_clique()->remove_land(s);
		s->set_my_clique(this);
		s->set_my_clique_id(clique_id);
		controlled_land.push_back(s);
		return temp;

	}
	bool clique::remove_land(state* s)
	{
		if (s->get_my_clique() == this)
			if (auto ptr = std::find_if(controlled_land.begin(), controlled_land.end(), [&](state * c) {return c == s; }); ptr != controlled_land.end())
					return controlled_land.erase(ptr), true;
		return false;
	}
}