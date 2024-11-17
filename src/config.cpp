#include <string>
#include <iostream>
#include <vector>
#include "utils/colorize.cpp"
#include "utils/files.cpp"
#include "utils/terminfo.cpp"
#include "utils/strings.cpp"
#include "terms/kitty.cpp"

struct config {
	std::string images_directory = "";
	unsigned int gap = 0;
	unsigned int padding_x = 0;
	unsigned int padding_y = 0;
	std::string text = "";
	char border = ' ';
	int border_color = 0;
	bool clear_console = false;
	bool crop_text_height = true;
};

int show_from_config(config conf) {
	std::string file_path = get_random_file_from_directory(conf.images_directory);
	if (file_path == "") {
		return 1;
	}

	fileInfo file = read_file(file_path);
	if (file.content.size() == 0 || file.img_width == 0 || file.img_height == 0) {
		log_error("couldn't load the image " + file_path);
		return 1;
	}

	if (conf.clear_console) {
		std::cout << dye::clear_console();
	}

	for (unsigned int i = 0; i < conf.padding_y; i++) {
		std::cout << '\n';
	}
	for (unsigned int i = 0; i < conf.padding_x; i++) {
		std::cout << ' ';
	}

	draw_png(file.content);
	
	std::pair<unsigned int, unsigned int> pixels_per_cell = get_pixels_per_cell();
	unsigned int img_cols = (file.img_width + pixels_per_cell.first - 1) / pixels_per_cell.first;
	unsigned int img_rows = (file.img_height + pixels_per_cell.second - 1) / pixels_per_cell.second;

	std::string formated_text = string_format(conf.text);
	std::vector<std::string> split = split_string(formated_text, '\n');
	for (unsigned int i = 0; i < split.size(); i++) {
		if (conf.crop_text_height && i >= img_rows) {
			break;
		}

		if (i == 0) {
			std::cout << repeat_spaces(img_cols + conf.gap);
		} else {
			std::cout << repeat_spaces(img_cols + conf.gap + conf.padding_x);
		}

		if (conf.border != ' ') {
			std::cout << dye::from(dye::unchanged, conf.border_color) << conf.border << ' ';
		}

		std::cout << dye::fg_reset() << split[i] << '\n';
	}

	for (unsigned int i = 0; i < conf.padding_y; i++) {
		std::cout << '\n';
	}

	return 0;
}
