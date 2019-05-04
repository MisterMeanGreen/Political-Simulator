#include "clique.h"


int clique::pub_clique_id = 0;
clique::clique(std::wstring n,int l_id) : clique_id(++pub_clique_id)
{
	leader_id = l_id;
	name = n;
}


clique::~clique()
{
}
bool clique::add_land(std::shared_ptr<map::state> s)
{
	if (s.use_count() == 2) {
		controlled_land.push_back(s);
		return true;
	}
	return false;
}
bool clique::remove_land(std::shared_ptr<map::state> s)
{
	for (auto ptr = controlled_land.begin(); ptr < controlled_land.end(); ptr++) {
		if (*ptr == s) {
			controlled_land.erase(ptr); return true;
		}
	}
	return false;
}
