#include "map.h"
namespace pol_sim {
	map::map(std::wifstream& file) {
		load_map_files(file);
	}
	map::map(std::wstring file_name)
	{
		std::wifstream temp(file_name);
		load_map_files(temp);
	}
	map::map()
	{
	}
	map::~map() {

	}
	state map::load_state(std::wifstream& file, wchar_t& last_char) { //Load a singular state
		auto load_until = [&](std::wstring chars) { return search_until(file, chars, last_char); };
		auto seek = [&](std::wstring chars) { return seek_until(file, chars, last_char); };
		auto load_string = [&]() { return load_quotes(file, last_char); };
		std::wstring current_text; //current text read
		std::wstring temp_state_name;
		std::vector<std::wstring> temp_state_neighbors;
		std::vector<COORD> temp_state_pixels;
		try {//Loading in name
			current_text = load_string();
			temp_state_name = current_text;
		}
		catch (std::wstring error_recieved) {
			throw L"ERROR : Failed to load state\n" + error_recieved + L"\n" + current_text;
		}
		try {//Loading neighbors
			seek(L"-");
			do {
				temp_state_neighbors.push_back(load_string());
				seek(L",-");
			} while (last_char != '-');
		}
		catch (std::wstring error_recieved) {
			throw L"ERROR : Failed to find neighbors when loading state : L" + error_recieved + L"\n" + temp_state_name;
		}
		try { //Loading Pixels
			seek(L"{");
			do {
				COORD temp_coord;
				current_text = load_until(L",");
				temp_coord.X = static_cast<SHORT>(stoi(current_text));
				current_text = load_until(L",}");
				temp_coord.Y = static_cast<SHORT>(stoi(current_text));
				temp_state_pixels.push_back(temp_coord);
			} while (last_char != '}');

		}
		catch (std::wstring error_recieved) {
			throw L"ERROR : Failed to load pixels \n" + error_recieved;
		}
		seek(L"-}");
		state temp_state(temp_state_name, temp_state_neighbors, temp_state_pixels,0,0,nullptr);
		return temp_state;
	}
	void map::load_map_files(std::wifstream& file) { //Loads in the map_display and the states information within the map
		wchar_t last_char; //Last character found
		auto load_until = [&](std::wstring chars) { return search_until(file, chars, last_char); };
		auto seek = [&](std::wstring chars) { return seek_until(file, chars, last_char); };
		auto load_string = [&]() { return load_quotes(file, last_char); };
		try {
			seek(L"M");
			seek(L"{");
			display = load_until(L"}");
		}
		catch (std::wstring exp) {
			throw L"ERROR : Failed to read display for map_file\n" + exp + L"\nData Read : " + display;
		}
		seek(L"D");
		seek(L"{");
		while (last_char != '}') {
			states.push_back(load_state(file, last_char));
		}
	}
	void map::render_state(std::wstring wstr, wchar_t chr, WORD color) {
		for (auto state : states)
			if (state.get_name() == wstr) {
				cursor::set_cur_color(color);
				for (auto pixel : state.get_pixels()) {
					cursor::set_cur_pos(pixel);
					std::wcout << chr;
				}
			}
	}
	void map::render_state(state s, wchar_t chr, WORD color)
	{
		cursor::set_cur_color(color);
		for (auto pixel : s.get_pixels()) {
			cursor::set_cur_pos(pixel);
			std::wcout << chr;
		}
	}
	state* map::state_at(COORD crd)
	{
		for (auto& state : states)
			for (auto& pixel : state.get_pixels())
				if (crd.X == pixel.X && crd.Y == pixel.Y)
					return &state;
		return nullptr;
	}
	state* map::operator[](size_t pos)
	{
		return &states[pos];
	}
	state* map::operator[](std::wstring s_name)
	{
		for (auto& state : states)
			if (state.get_name() == s_name)
				return &state;
		return nullptr;
	}
	std::wstring map::get_display()
	{
		return display;
	}
	void map::operator()(std::wifstream & file)
	{
		display = L"";
		states.clear();
		load_map_files(file);
	}
	void map::operator()(std::wstring & file_name)
	{
		std::wifstream file(file_name, std::ios::binary);
		display = L"";
		states.clear();
		load_map_files(file);
	}
}
