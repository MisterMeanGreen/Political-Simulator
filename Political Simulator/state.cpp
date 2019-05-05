#include "state.h"

namespace pol_sim {
	state::state(int p_id, std::wstring p_name, std::vector<std::wstring> p_neighbors, std::vector<COORD> p_pixels)
	{
		clique_id = p_id;
		name = p_name;
		neighbors = p_neighbors;
		pixels = p_pixels;
	}
	state::state() {
		clique_id = state::null;
		name = L"NULL";
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
	size_t state::get_clique_id()
	{
		return clique_id;
	}
	clique * state::get_my_clique()
	{
		return my_clique;
	}
	size_t state::set_clique_id(size_t id)
	{
		return clique_id = id;
	}
	std::wstring state::set_name(std::wstring new_name)
	{
		return name = new_name;
	}
	void state::set_my_clique(clique* c)
	{
		my_clique = c;
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