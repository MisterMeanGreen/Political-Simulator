#include "state.h"

namespace pol_sim {
	state::state(std::wstring p_name, std::vector<std::wstring> p_neighbors, std::vector<COORD> p_pixels,int p_inc,int p_pop,clique* c_ptr)
	{
		income = p_inc;
		population = p_pop;
		name = p_name;
		neighbors = p_neighbors;
		pixels = p_pixels;
		my_clique = c_ptr;
	}
	state::state() {
		income = 0;
		population = 0;
		name = L"NULL";
		my_clique = nullptr;
	}
	state::~state() {}
	bool state::is_neighbor(std::wstring p_neighbor)
	{
		for (std::wstring neighbor : neighbors)
			if (neighbor == p_neighbor)
				return true;
		return false;
	}
	bool state::is_neighbor(state p_neighbor)
	{
		return is_neighbor(p_neighbor.get_name());
	}
	const std::vector<COORD>& state::get_pixels() {
		return pixels;
	}
	std::wstring state::get_name()
	{
		return name;
	}
	clique * state::get_my_clique()
	{
		return my_clique;
	}
	size_t state::get_my_clique_id()
	{
		return my_clique_id;
	}
	std::wstring state::set_name(std::wstring new_name)
	{
		return name = new_name;
	}
	clique* state::set_my_clique(clique* c)
	{
		return my_clique = c;
	}
	size_t state::set_my_clique_id(size_t _id)
	{
		return my_clique_id = _id;
	}
	COORD state::avg_coord() {
		COORD temp_avg = { 0,0 };
		for (auto crd : pixels) {
			temp_avg.X += crd.X;
			temp_avg.Y += crd.Y;
		}
		temp_avg.X /= static_cast<SHORT>(pixels.size());
		temp_avg.Y /= static_cast<SHORT>(pixels.size());
		return temp_avg;
	}
}