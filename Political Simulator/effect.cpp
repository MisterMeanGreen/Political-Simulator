
#include "effect.h"

effect::effect(std::wstring p_name, std::wstring p_desc, int p_diplo, int p_int, int p_app, int p_comm) {
	name = p_name;
	description = p_desc;
	diplomacy = p_diplo;
	intrigue = p_int;
	appeal = p_app;
	command = p_comm;
}
effect::effect() {
	name = L"NULL";
	description = L"NULL";
	diplomacy = 0;
	intrigue = 0;
	appeal = 0;
	command = 0; //Debug values to easily tell what values have been set when debugging
}
effect::~effect() {}
bool effect::operator==(effect x) {
	return name == x.name;
}
bool effect::operator!=(effect x) {
	return name != x.name;
}
bool effect::contains_ntrait(std::wstring s) {
	for (auto x : negative_traits)
		if (x == s)
			return true;
	return false;
}
std::vector<effect> traits;
std::vector<std::wstring> m_names;
std::vector<std::wstring> f_names;
std::vector<std::wstring> l_names;
std::wostream &operator<<(std::wostream& os, effect const &temp_effect) {
	return os << L"\nName : L" + temp_effect.name << L"\nDesc : L" + temp_effect.description << L"\nDiplomacy : L" << std::to_wstring(temp_effect.diplomacy) << L"\nIntrigue : L" << std::to_wstring(temp_effect.intrigue) << L"\nAppeal : L" << std::to_wstring(temp_effect.appeal) << L"\nCommand : L" << std::to_wstring(temp_effect.command);
}
