#include <cassert>
#include "utils/color.cpp"

void color_red() {
	assert(dye::rgb_color_code(255, 0, 0) == 196);
}

void color_custom() {
	assert(dye::rgb_color_code(211, 241, 223) == 194);
	assert(dye::rgb_color_code(82, 91, 68) == 59);
}

void hex_red() {
	rgb clong = hex_to_rgb("ff0000");
	assert(clong.r == 255 && clong.g == 0 && clong.b == 0);

	rgb cshort = hex_to_rgb("f00");
	assert(cshort.r == 255 && clong.g == 0 && clong.b == 0);
}

void hex_custom() {
	rgb f = hex_to_rgb("D3F1DF");
	assert(f.r == 211 && f.g == 241 && f.b == 223);
}

void hex_term_colors() {
	rgb first = hex_to_rgb("d0d0d0");
	assert(dye::rgb_color_code(first) == 188);
}

int main() {
	color_red();
	color_custom();
	hex_red();
	hex_custom();
	hex_term_colors();

	return 0;
}
