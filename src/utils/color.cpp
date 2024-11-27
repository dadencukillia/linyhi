#ifndef D_COLOR_CPP
#define D_COLOR_CPP

#include <cctype>
#include <iostream>
#include <string>

struct rgb {
	unsigned short r;
	unsigned short g;
	unsigned short b;
};

namespace dye {
	constexpr int reset = 0;
	constexpr int unchanged = 1;

	namespace fg {
		constexpr int black = 30;
		constexpr int red = 31;
		constexpr int green = 32;
		constexpr int yellow = 33;
		constexpr int blue = 34;
		constexpr int magenta = 35;
		constexpr int cyan = 36;
		constexpr int white = 37;
		constexpr int gray = 90;
		constexpr int bright_red = 91;
		constexpr int bright_green = 92;
		constexpr int bright_yellow = 93;
		constexpr int bright_blue = 94;
		constexpr int bright_magenta = 95;
		constexpr int bright_cyan = 96;
		constexpr int bright_white = 97;
	}

	namespace bg {
		constexpr int black = 40;
		constexpr int red = 41;
		constexpr int green = 42;
		constexpr int yellow = 43;
		constexpr int blue = 44;
		constexpr int magenta = 45;
		constexpr int cyan = 46;
		constexpr int white = 47;
		constexpr int gray = 100;
		constexpr int bright_red = 101;
		constexpr int bright_green = 102;
		constexpr int bright_yellow = 103;
		constexpr int bright_blue = 104;
		constexpr int bright_magenta = 105;
		constexpr int bright_cyan = 106;
		constexpr int bright_white = 107;
	}

	std::string from(int bg, int fg) {
		return "\e[" + std::to_string(fg) + ";" + std::to_string(bg) + "m";
	}

	std::string on_black() {
		return from(bg::black, unchanged);
	}

	std::string on_red() {
		return from(bg::red, unchanged);
	}

	std::string on_green() {
		return from(bg::green, unchanged);
	}

	std::string on_yellow() {
		return from(bg::yellow, unchanged);
	}

	std::string on_blue() {
		return from(bg::blue, unchanged);
	}

	std::string on_magenta() {
		return from(bg::magenta, unchanged);
	}

	std::string on_cyan() {
		return from(bg::cyan, unchanged);
	}

	std::string on_white() {
		return from(bg::white, unchanged);
	}

	std::string on_gray() {
		return from(bg::gray, unchanged);
	}

	std::string on_bright_red() {
		return from(bg::bright_red, unchanged);
	}

	std::string on_bright_green() {
		return from(bg::bright_green, unchanged);
	}

	std::string on_bright_yellow() {
		return from(bg::bright_yellow, unchanged);
	}

	std::string on_bright_blue() {
		return from(bg::bright_blue, unchanged);
	}

	std::string on_bright_magenta() {
		return from(bg::bright_magenta, unchanged);
	}

	std::string on_bright_cyan() {
		return from(bg::bright_cyan, unchanged);
	}

	std::string on_bright_white() {
		return from(bg::bright_white, unchanged);
	}

	std::string bg_reset() {
		return from(reset, unchanged);
	}

	std::string black() {
		return from(unchanged, fg::black);
	}

	std::string red() {
		return from(unchanged, fg::red);
	}

	std::string green() {
		return from(unchanged, fg::green);
	}

	std::string yellow() {
		return from(unchanged, fg::yellow);
	}

	std::string blue() {
		return from(unchanged, fg::blue);
	}

	std::string magenta() {
		return from(unchanged, fg::magenta);
	}

	std::string cyan() {
		return from(unchanged, fg::cyan);
	}

	std::string white() {
		return from(unchanged, fg::white);
	}

	std::string gray() {
		return from(unchanged, fg::gray);
	}

	std::string bright_red() {
		return from(unchanged, fg::bright_red);
	}

	std::string bright_green() {
		return from(unchanged, fg::bright_green);
	}

	std::string bright_yellow() {
		return from(unchanged, fg::bright_yellow);
	}

	std::string bright_blue() {
		return from(unchanged, fg::bright_blue);
	}

	std::string bright_magenta() {
		return from(unchanged, fg::bright_magenta);
	}

	std::string bright_cyan() {
		return from(unchanged, fg::bright_cyan);
	}

	std::string bright_white() {
		return from(unchanged, fg::bright_white);
	}

	std::string fg_reset() {
		return from(unchanged, reset);
	}

	std::string both_reset() {
		return from(reset, reset);
	}

	std::string clear_console() {
		return "\033[2J\033[3J\033[1;1H";
	}

	unsigned int rgb_color_code(unsigned short r, unsigned short g, unsigned short b) {
		unsigned short v[] = {0, 95, 135, 175, 215, 255};
		size_t size = sizeof(v) / sizeof(unsigned short);
		unsigned short r_diff_index = size-1;
		unsigned short r_diff_value = v[size-1];
		unsigned short g_diff_index = size-1;
		unsigned short g_diff_value = v[size-1];
		unsigned short b_diff_index = size-1;
		unsigned short b_diff_value = v[size-1];

		for (int i = 0; i < size; i++) {
			unsigned short vl = v[i];
			unsigned short rv = 0;
			unsigned short gv = 0;
			unsigned short bv = 0;

			if (vl < r) {
				rv = r-vl;
			} else {
				rv = vl-r;
			}

			if (vl < g) {
				gv = g-vl;
			} else {
				gv = vl-g;
			}

			if (vl < b) {
				bv = b-vl;
			} else {
				bv = vl-b;
			}

			if (rv < r_diff_value) {
				r_diff_value = rv;
				r_diff_index = i;
			}
			if (gv < g_diff_value) {
				g_diff_value = gv;
				g_diff_index = i;
			}
			if (bv < b_diff_value) {
				b_diff_value = bv;
				b_diff_index = i;
			}
		}

		return r_diff_index * size * size + g_diff_index * size + b_diff_index + 16;
	}

	unsigned int rgb_color_code(rgb color) {
		return rgb_color_code(color.r, color.g, color.b);
	}

	std::string bg_from_rgb(unsigned short r, unsigned short g, unsigned short b) {
		return "\e[48:5:" + std::to_string(rgb_color_code(r, g, b)) + "m";
	}

	std::string fg_from_rgb(unsigned short r, unsigned short g, unsigned short b) {
		return "\e[38:5:" + std::to_string(rgb_color_code(r, g, b)) + "m";
	}

	std::string bg_from_rgb(rgb color) {
		return bg_from_rgb(color.r, color.g, color.b);
	}

	std::string fg_from_rgb(rgb color) {
		return fg_from_rgb(color.r, color.g, color.b);
	}
}

rgb hex_to_rgb(std::string hex) {
	char symbols[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f'};
	unsigned short c[2] = {16, 16};
	bool shorten;
	if (hex.length() == 6) {
		shorten = false;
	} else if (hex.length() == 3) {
		shorten = true;
	} else {
		return rgb{};
	}

	rgb color = {16, 16, 16};

	for (char i : hex) {
		char lower = std::tolower(i);
		bool contains = false;
		unsigned short value = 0;
		for (int ci = 0; ci < sizeof(symbols); ci++) {
			if (symbols[ci] == lower) {
				contains = true;
				value = ci;
				break;
			}
		}

		if (!contains) {
			return rgb{};
		}

		if (shorten) {
			if (color.r == 16) {
				color.r = value * 16 + value;
			} else if (color.g == 16) {
				color.g = value * 16 + value;
			} else if (color.b == 16) {
				color.b = value * 16 + value;
			}
		} else {
			if (c[0] == 16) {
				c[0] = value;
			} else {
				c[1] = value;

				if (color.r == 16) {
					color.r = c[0] * 16 + c[1];
				} else if (color.g == 16) {
					color.g = c[0] * 16 + c[1];
				} else if (color.b == 16) {
					color.b = c[0] * 16 + c[1];
				}

				c[0] = 16;
				c[1] = 16;
			}
		}
	}

	return color;
}

void log_error(std::string error) {
	std::cerr << dye::red() << "Error: " << dye::fg_reset() << error << std::endl;
}

#endif
