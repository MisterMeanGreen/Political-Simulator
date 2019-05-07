#pragma once
#include <list>
#include <string>
#include <iostream>
#include <vector>
#include <fstream>

#include "map.h"
#include "person.h"
#include "clique.h"
#include "unicode.h"
#include "load.h"
#include "cursor.h"


namespace pol_sim {
	class engine
	{

	public:
		map game_map;
		std::list<person> people;
		std::list<clique> nations;
		std::vector<std::wstring> path_names;
		engine(std::wstring paths);
		~engine();
		void render_map();
		void set_title(std::wstring title);
	};
}
