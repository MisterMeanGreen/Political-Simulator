#include "cursor.h"



cursor::cursor() : curr_pos({ 0,0 }), curr_char(0), color(0x0f) { draw(); }
cursor::cursor(COORD pos) : curr_pos(pos), curr_char(0), color(0x0f) { draw(); }
cursor::cursor(wchar_t chr) : curr_pos({ 0,0 }), curr_char(chr), color(0x0f) { draw(); }
cursor::cursor(COORD pos, wchar_t chr) : curr_pos(pos), curr_char(chr), color(0x0f) { draw(); }
cursor::cursor(COORD pos, wchar_t chr, WORD clr) : curr_pos(pos), curr_char(chr), color(clr) { draw(); }
cursor::~cursor() {}

void cursor::move_to(COORD pos)
{
	clear();
	set_pos(pos);
	draw();
}

COORD cursor::get_pos()
{
	return curr_pos;
}

void cursor::set_pos(COORD pos)
{
	curr_pos = pos;
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
	set_color(last_color);
	::set_pos(curr_pos);
	std::wcout << last_char;
}
void cursor::draw()
{
	last_color = ::get_charinfo(curr_pos);
	last_char = ::get_char(curr_pos);
	set_color(color);
	::set_pos(curr_pos);
	std::wcout << curr_char;
}

WORD cursor::get_char()
{
	return curr_char;
}
