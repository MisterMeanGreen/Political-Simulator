#include "clique.h"

namespace pol_sim {
	size_t clique::pub_clique_id = 0;
	clique::clique(std::wstring n, int l_id) : clique_id(++pub_clique_id)
	{
		leader_id = l_id;
		name = n;
	}


	clique::~clique()
	{
	}
	size_t clique::get_id()
	{
		return clique_id;
	}
	std::wstring clique::get_name()
	{
		return name;
	}
	size_t clique::add_land(state* s)
	{
		for (auto c_l : controlled_land)
			if (s == c_l)
				return clique_id;

		size_t temp = s->get_clique_id();
		s->set_clique_id(clique_id);
		controlled_land.push_back(s);
		return temp;

	}
	bool clique::remove_land(state* s)
	{
		for (auto ptr = controlled_land.begin(); ptr < controlled_land.end(); ptr++) {
			if (*ptr == s) {
				controlled_land.erase(ptr);
				return true;
			}
		}
		return false;
	}
}