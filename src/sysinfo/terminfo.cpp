#include <cstdlib>
#include <string>
#include <sys/ioctl.h>
#include <unistd.h>
#include <utility>
#include "../utils/command.cpp"

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

std::string get_term_name() {
	std::string term = std::getenv("TERM")?:"";
	std::string result = "";

	for (char i : term) {
		if (i == '-' && result == "xterm") {
			result.clear();
		} else {
			result.push_back(i);
		}
	}

	return result;
}

std::string get_shell_name() {
	std::string shell_path = std::getenv("SHELL")?:"";
	std::string shell_name = "";

	for (char i : shell_path) {
		if (i == '/' || i == '\\') {
			shell_name.clear();
		} else {
			shell_name.push_back(i);
		}
	}

	return shell_name;
}

std::string get_shell_version() {
	std::string shell_path = std::getenv("SHELL")?:"";
	std::string shell_name = "";

	for (char i : shell_path) {
		if (i == '/' || i == '\\') {
			shell_name.clear();
		} else {
			shell_name.push_back(std::toupper(i));
		}
	}
	std::string shell_version = exec((shell_path + " -c \"printf %s \\$" + shell_name + "_VERSION\"").c_str());

	return shell_version;
}
