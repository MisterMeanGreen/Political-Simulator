#include "clique.h"

namespace pol_sim {
	size_t clique::pub_clique_id = 0;
	clique::clique(std::wstring n, wchar_t s, DWORD c) : clique_id(++pub_clique_id)
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
	size_t clique::add_land(state* s)
	{
		for (auto c_l : controlled_land)
			if (s == c_l)
				return clique_id;

		size_t temp = s->get_clique_id();
		s->get_my_clique()->remove_land(s);
		s->set_my_clique(this);
		s->set_clique_id(clique_id);
		controlled_land.push_back(s);
		return temp;

	}
	bool clique::remove_land(state* s)
	{
		if (s->get_clique_id() != state::null) {
			for (auto ptr = controlled_land.begin(); ptr < controlled_land.end(); ptr++) {
				if (*ptr == s) {
					s->set_clique_id(state::null);
					controlled_land.erase(ptr);
					return true;
				}
			}
		}
		return false;
	}
}