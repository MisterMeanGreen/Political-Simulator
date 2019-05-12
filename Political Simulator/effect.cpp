
#include "effect.h"
namespace pol_sim {
	const std::array<std::wstring, 4> effect::effect_stat_id_names = { L"diplomacy",L"intrigue",L"appeal",L"command" };
	effect::effect(const std::wstring& p_name, const std::wstring& p_desc, const std::map<std::wstring, int>& p_effects, const std::vector<std::wstring>& p_negative_traits) {
		name = p_name;
		description = p_desc;
		stat_effects = p_effects;
		negative_traits = p_negative_traits;
	}
	int effect::get_stat(std::wstring stat)
	{
		return stat_effects[stat];
	}
	std::wstring effect::get_name()
	{
		return name;
	}
	std::wstring effect::get_description()
	{
		return description;
	}
	int effect::set_stat(std::wstring stat, int amount)
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
}