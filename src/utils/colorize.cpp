#ifndef D_COLORIZE_CPP
#define D_COLORIZE_CPP

#include <iostream>
#include <string>

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
}

void log_error(std::string error) {
	std::cerr << dye::red() << "Error: " << dye::fg_reset() << error << std::endl;
}

#endif
