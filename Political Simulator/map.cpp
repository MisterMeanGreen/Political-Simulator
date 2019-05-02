#include "map.h"


map::state::state(int p_id, std::wstring p_name) {
	clique_id = p_id;
	name = p_name;
}
map::state::state(int p_id) {
	clique_id = p_id;
}
map::state::~state() {}
const auto& map::state::get_neighbors() {
	return neighbors;
}
map::state map::load_state(std::wifstream& file, wchar_t& last_char) { //Load a singular state
	auto load_until = [&](std::wstring chars) { return search_until(file, chars, last_char); };
	auto load_string = [&]() { return load_quotes(file, last_char); };
	std::wstring current_text; //current text read
	state temp_state(0);
	try {//Loading in name
		current_text = load_string();
		temp_state.name = current_text;
	}
	catch (std::wstring error_recieved) {
		throw L"ERROR : Failed to load state\n" + error_recieved + L"\n" + current_text;
	}
	try {//Loading neighbors
		load_until(L"-");
		do {
			temp_state.neighbors.push_back(load_string());
			load_until(L",-");
		} while (last_char != '-');
	}
	catch (std::wstring error_recieved) {
		throw L"ERROR : Failed to find neighbors when loading state : L" + error_recieved + L"\n" + temp_state.name;
	}
	try { //Loading Pixels
		load_until(L"{");
		do {
			COORD temp_coord;
			current_text = load_until(L",");
			temp_coord.X = static_cast<SHORT>(stoi(current_text));
			current_text = load_until(L",}");
			temp_coord.Y = static_cast<SHORT>(stoi(current_text));
			temp_state.pixels.push_back(temp_coord);
		} while (last_char != '}');

	}
	catch (std::wstring error_recieved) {
		throw L"ERROR : Failed to load pixels \n" + error_recieved;
	}
	load_until(L"-}");
	return temp_state;
}
COORD map::state::avg_coord() {
	COORD temp_avg = { 0,0 };
	for (auto crd : pixels) {
		temp_avg.X += crd.X;
		temp_avg.Y += crd.Y;
	}
	temp_avg.X /= static_cast<SHORT>(pixels.size());
	temp_avg.Y /= static_cast<SHORT>(pixels.size());
	return temp_avg;
}
void map::load_map_files() { //Loads in the map_display and the states information within the map
	std::wifstream map_file(L"USA.txt");
	wchar_t last_char; //Last character found
	auto load_until = [&](std::wstring chars) { return search_until(map_file, chars, last_char); };
	auto load_string = [&]() { return load_quotes(map_file, last_char); };
	try {
		load_until(L"M");
		load_until(L"{");
		display = load_until(L"}");
	}
	catch (std::wstring exp) {
		throw L"ERROR : Failed to read display for map_file\n" + exp + L"\nData Read : " + display;
	}
	load_until(L"D");
	load_until(L"{");
	while (last_char != '}') {
		states.push_back(load_state(map_file, last_char));
	}
}
void map::render_state(std::wstring wstr, wchar_t chr, WORD color) {
	for (auto state : states)
		if (state.name == wstr) {
			cursor::set_cur_color(color);
			for (auto pixel : state.pixels) {
				cursor::set_cur_pos(pixel);
				std::wcout << chr;
			}
		}
}
