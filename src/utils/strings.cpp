#ifndef D_STRINGS_CPP
#define D_STRINGS_CPP

#include <cstdlib>
#include <string>
#include <vector>

std::string repeat_spaces(unsigned int spaces) {
	std::string str;
	str.reserve(spaces);
	for (int i = 0; i < spaces; i++) {
		str.push_back(' ');
	}
	return str;
}

std::vector<std::string> split_string(std::string str, char sep) {
	std::vector<std::string> vec;

	std::string part = "";
	for (char i : str) {
		if (i == sep) {
			vec.push_back(part);
			part = "";
		} else {
			part.push_back(i);
		}
	}
	if (!part.empty()) {
		vec.push_back(part);
	}

	return vec;
}

#endif
