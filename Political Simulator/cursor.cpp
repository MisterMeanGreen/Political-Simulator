#include "cursor.h"
namespace pol_sim {
	HANDLE cursor::hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	DWORD cursor::num_read;
	void cursor::set_cur_color(WORD color) {
		if (!SetConsoleTextAttribute(hConsole, color)) {
			throw L"ERROR : Set color error\nColor : " + color;
		}
	}
	void cursor::set_cur_pos(COORD crd) {
		if (!SetConsoleCursorPosition(hConsole, crd)) {
			throw L"ERROR : Set console position error\nX : " + std::to_wstring(crd.X) + L"\nY : " + std::to_wstring(crd.Y);
		}
	}
	wchar_t cursor::get_cur_char(COORD crd)
	{
		wchar_t temp;
		ReadConsoleOutputCharacter(hConsole, &temp, 1, crd, &num_read);
		return temp;
	}
	WORD cursor::get_cur_charinfo(COORD crd)
	{
		WORD temp;
		ReadConsoleOutputAttribute(hConsole, &temp, 1, crd, &num_read);
		return temp;
	}
	COORD cursor::get_l_bound()
	{
		return lower_B;
	}
	COORD cursor::get_h_bound()
	{
		return upper_B;
	}
	void cursor::set_bounds(COORD lower, COORD upper)
	{
		lower_B = lower, upper_B = upper;
	}
	cursor::cursor() : cursor({ 0,0 }, L'X', 0x0f) { }
	cursor::cursor(COORD pos) : cursor(pos, L'X', 0x0f) {  }
	cursor::cursor(wchar_t chr) : cursor({ 0,0 }, chr, 0x0f) { }
	cursor::cursor(COORD pos, wchar_t chr) : cursor(pos, chr, 0x0f) { }
	cursor::cursor(COORD pos, wchar_t chr, WORD clr) : curr_pos(pos), curr_char(chr), color(clr), last_char('\0'), last_color(0), lower_B({ 0,0 }), upper_B({ 120,SHRT_MAX }) {  draw(); }
	cursor::~cursor() {}

	void cursor::move_to(COORD pos)
	{
		clear();
		set_pos(pos);
		draw();
	}

	void cursor::redraw()
	{
		clear();
		draw();
	}

	COORD cursor::get_pos()
	{
		return curr_pos;
	}

	void cursor::set_pos(COORD pos)
	{
		//Clamp gurantees within bounds
		curr_pos = { std::clamp(pos.X,lower_B.X,upper_B.X), std::clamp(pos.Y, lower_B.Y, upper_B.Y) };
	}

	void cursor::set_char(wchar_t chr)
	{
		curr_char = chr;
	}

	void cursor::set_attr(WORD chr)
	{
		color = chr;
	}
	void cursor::clear() {
		set_cur_color(last_color);
		set_cur_pos(curr_pos);
		std::wcout << last_char;
	}
	void cursor::draw()
	{
		last_color = get_cur_charinfo(curr_pos);
		last_char = get_cur_char(curr_pos);
		set_cur_color(color);
		set_cur_pos(curr_pos);
		std::wcout << curr_char;
	}

	WORD cursor::get_char()
	{
		return curr_char;
	}
}