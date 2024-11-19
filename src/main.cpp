#include "config.cpp"
#include "utils/files.cpp"
#include "utils/lh_parser.cpp"
#include <cctype>
#include <filesystem>
#include <vector>

int fg_color_from_name(std::string name) {
	std::string n = "";
	for (char i : name) {
		if (std::isalpha(i)) {
			n.push_back(std::tolower(i));
		}
	}

	if (n == "black") {
		return dye::fg::black;
	} else if (n == "red") {
		return dye::fg::red;
	} else if (n == "green") {
		return dye::fg::green;
	} else if (n == "yellow") {
		return dye::fg::yellow;
	} else if (n == "blue") {
		return dye::fg::blue;
	} else if (n == "magenta") {
		return dye::fg::magenta;
	} else if (n == "cyan") {
		return dye::fg::cyan;
	} else if (n == "white") {
		return dye::fg::white;
	} else if (n == "gray" || n == "grey" || n == "brightblack") {
		return dye::fg::gray;
	} else if (n == "brightred") {
		return dye::fg::bright_red;
	} else if (n == "brightgreen") {
		return dye::fg::bright_green;
	} else if (n == "brightyellow") {
		return dye::fg::bright_yellow;
	} else if (n == "birghtblue") {
		return dye::fg::bright_blue;
	} else if (n == "brightmagenta") {
		return dye::fg::bright_magenta;
	} else if (n == "brightcyan") {
		return dye::fg::bright_cyan;
	} else if (n == "brightwhite") {
		return dye::fg::bright_white;
	} else {
		return 0;
	}
}

int main() {
	std::filesystem::path config_directory = replace_tilde_path("~/.config/linyhi");

	std::vector<field> fields = {
		field(datatype::STRING, "textfile"),
		field(datatype::STRING, "imagesdirectory"),
		field(datatype::ULONG, "paddingx"),
		field(datatype::ULONG, "paddingy"),
		field(datatype::ULONG, "gap"),
		field(datatype::BOOL, "clearconsole"),
		field(datatype::BOOL, "croptextheight"),
		field(datatype::CHAR, "border"),
		field(datatype::STRING, "bordercolor"),
	};
	parse_settings settings {
		(config_directory / "config.lh").string(),
		fields
	};

	parsing_result result = parse(settings);
	if (!result.success) {
		return 1;
	}


	config conf;
	if (result.strings.find("textfile") != result.strings.end()) {
		std::string path = (config_directory / replace_tilde_path(result.strings["textfile"])).string();
		file_info file = read_file(path);
		if (!file.opened) {
			log_error("couldn't open file " + path);
			return 1;
		}

		std::string content = "";
		for (char i : file.content) {
			content.push_back(i);
		}

		conf.text = content;
	}
	if (result.strings.find("imagesdirectory") != result.strings.end()) {
		conf.images_directory = (config_directory / replace_tilde_path(result.strings["imagesdirectory"])).string();
	}
	if (result.strings.find("bordercolor") != result.strings.end()) {
		conf.border_color = fg_color_from_name(result.strings["bordercolor"]);
	}
	if (result.ulongs.find("paddingx") != result.ulongs.end()) {
		conf.padding_x = result.ulongs["paddingx"];
	}
	if (result.ulongs.find("paddingy") != result.ulongs.end()) {
		conf.padding_y = result.ulongs["paddingy"];
	}
	if (result.ulongs.find("gap") != result.ulongs.end()) {
		conf.gap = result.ulongs["gap"];
	}
	if (result.bools.find("clearconsole") != result.bools.end()) {
		conf.clear_console = result.bools["clearconsole"];
	}
	if (result.bools.find("croptextheight") != result.bools.end()) {
		conf.crop_text_height = result.bools["croptextheight"];
	}
	if (result.chars.find("border") != result.chars.end()) {
		conf.border = result.chars["border"];
	}

	return show_from_config(conf);
}
