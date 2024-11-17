#ifndef D_TERMINFO_CPP
#define D_TERMINFO_CPP

#include <sys/ioctl.h>
#include <utility>

std::pair<unsigned int, unsigned int> get_term_size() {
	struct winsize sz;
    ioctl(0, TIOCGWINSZ, &sz);

	return {sz.ws_xpixel, sz.ws_ypixel};
}

std::pair<unsigned int, unsigned int> get_term_cells() {
	struct winsize sz;
	ioctl(0, TIOCGWINSZ, &sz);

	return {sz.ws_col, sz.ws_row};
}

std::pair<unsigned int, unsigned int> get_pixels_per_cell() {
	struct winsize sz;
	ioctl(0, TIOCGWINSZ, &sz);

	return {sz.ws_xpixel / sz.ws_col, sz.ws_ypixel / sz.ws_row};
}

#endif
