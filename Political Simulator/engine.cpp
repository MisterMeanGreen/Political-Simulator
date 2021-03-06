#include "engine.h"


namespace pol_sim {
	engine::engine(std::wstring paths) : game_map()
	{
		//Loads files
		init_locale();
		wchar_t last_char;
		std::wifstream path_finder(paths,std::ios::binary);
		auto load_until = [&](std::wstring chars) { return search_until(path_finder, chars, last_char); };
		auto seek = [&](std::wstring chars) { return seek_until(path_finder, chars, last_char); };
		auto load_string = [&]() { return load_quotes(path_finder, last_char); };
		seek(L"P");
		seek(L"{");
		path_names.push_back(load_string());
		seek(L"T");
		path_names.push_back(load_string());
		seek(L"N");
		path_names.push_back(load_string());
		seek(L"}");
		game_map(path_names[0]);
		person::load_player_files(path_names[1], path_names[2]);


	}


	engine::~engine()
	{
	}
	void engine::render_map()
	{
		cursor::set_cur_pos({ 0,0 });
		std::wcout << game_map.get_display();
		for (auto clique : nations)
			clique.render_clique();

	}
	void engine::set_title(std::wstring title)
	{
		SetConsoleTitle(title.c_str());
	}
}