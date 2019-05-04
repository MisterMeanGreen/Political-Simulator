
#include "effect.h"

effect::effect(std::wstring p_name, std::wstring p_desc, int p_diplo, int p_int, int p_app, int p_comm) {
	stat_effects.resize(STAT_SIZE);
	name = p_name;
	description = p_desc;
	stat_effects[stat_ids::diplomacy] = p_diplo;
	stat_effects[stat_ids::intrigue] = p_int;
	stat_effects[stat_ids::appeal] = p_app;
	stat_effects[stat_ids::command] = p_comm;
}
effect::effect() : effect(L"NULL",L"NULL",0,0,0,0) {}
effect::~effect() {}
int effect::get_stat(size_t stat)
{
	return stat_effects[stat];
}
int effect::set_stat(size_t stat, int amount)
{
	return stat_effects[stat] = amount;
}
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
std::wostream &operator<<(std::wostream& os, effect const &temp_effect) {
	return os << L"\nName : L" + temp_effect.name << L"\nDesc : L" + temp_effect.description << L"\nDiplomacy : L" << std::to_wstring(temp_effect.diplomacy) << L"\nIntrigue : L" << std::to_wstring(temp_effect.intrigue) << L"\nAppeal : L" << std::to_wstring(temp_effect.appeal) << L"\nCommand : L" << std::to_wstring(temp_effect.command);
}
