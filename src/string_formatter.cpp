#ifndef D_STRING_FORMATTER_CPP
#define D_STRING_FORMATTER_CPP

#include <string>
#include "utils/colorize.cpp"

std::string format_value(std::string key) {
	// Colors
	if (key == "black") {
		return dye::black();
	} else if (key == "red") {
		return dye::red();
	} else if (key == "green") {
		return dye::green();
	} else if (key == "yellow") {
		return dye::yellow();
	} else if (key == "blue") {
		return dye::blue();
	} else if (key == "magenta") {
		return dye::magenta();
	} else if (key == "cyan") {
		return dye::cyan();
	} else if (key == "white") {
		return dye::white();
	} else if (key == "gray") {
		return dye::gray();
	} else if (key == "bright_red") {
		return dye::bright_red();
	} else if (key == "bright_green") {
		return dye::bright_green();
	} else if (key == "bright_yellow") {
		return dye::bright_yellow();
	} else if (key == "bright_blue") {
		return dye::bright_blue();
	} else if (key == "bright_magenta") {
		return dye::bright_magenta();
	} else if (key == "bright_cyan") {
		return dye::bright_cyan();
	} else if (key == "bright_white") {
		return dye::bright_white();
	} else if (key == "reset") {
		return dye::fg_reset();
	}

	// System variables
	else {
		char *env = std::getenv(key.c_str());
		if (env == nullptr) {
			return "%" + key + "%";
		} else {
			return std::string(env);
		}
	}
}

std::string string_format(std::string str) {
	std::string out = "";
	bool slashed = false;
	bool opened = false;
	std::string key = "";
	char var_sym = '%';

	for (char i : str) {
		if (slashed) {
			if (i == '%') {
				out.push_back(i);
			} else {
				out.push_back('\\');
				out.push_back(i);
			}
			slashed = false;
		} else if (opened) {
			if (i == ' ') {
				out.push_back(var_sym);
				out.append(key);
				key = "";
				opened = false;
			} else if (i == '%') {
				out.append(format_value(key));
				key = "";
				opened = false;
			} else {
				key.push_back(i);
			}
		} else {
			if (i == '\\') {
				slashed = true;
			} else if (i == '%') {
				opened = true;
			} else {
				out.push_back(i);
			}
		}
	}
	if (slashed) {
		out.push_back('\\');
	}
	if (opened) {
		out.push_back('%');
		out.append(key);
	}
	return out;
}

#endif
