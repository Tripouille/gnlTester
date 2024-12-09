#include "color.hpp"

extern bool is_initializing;

std::ostream &
operator<<(std::ostream & os, Color c)
{
	bool old_is_initializing = is_initializing;
	is_initializing = true;
	std::basic_ostream<char, std::char_traits<char> > &basicOstream =
			os << "\e[" << static_cast<int>(c) << "m";
	is_initializing = old_is_initializing;
	return basicOstream;
}
