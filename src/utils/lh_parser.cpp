#ifndef D_LH_PARSER_CPP
#define D_LH_PARSER_CPP

#include <cctype>
#include <cstdlib>
#include <stdexcept>
#include <string>
#include <map>
#include <vector>
#include "files.cpp"
#include "strings.cpp"

enum datatype {
	STRING,
	CHAR,
	LONG,
	ULONG,
	BOOL
};

struct field {
	datatype type;
	std::string name;

	field(datatype type, std::string name) : type(type), name(name) {}
};

struct parse_settings {
	std::string path;
	std::vector<field> fields;
};

struct parsing_result {
	bool success;
	std::map<std::string, std::string> strings;
	std::map<std::string, char> chars;
	std::map<std::string, long> longs;
	std::map<std::string, unsigned long> ulongs;
	std::map<std::string, bool> bools;
};

parsing_result parse(parse_settings settings) {
	file_info file = read_file(settings.path);
	if (!file.opened) {
		log_error("couldn't open config file " + settings.path);
		return {};
	}

	parsing_result result { false };

	std::vector<std::string> lines = split_string(file.content, '\n');
	for (int index = 0; index < lines.size(); index++) {
		std::string line = lines[index];

		bool skip = false;
		bool keyEntering = true;
		std::string key = "";
		std::string value = "";

		bool quoted = false;
		bool slashed = false;

		for (char i : line) {
			if (keyEntering) {
				if (i == ' ') {
					if (!key.empty()) {
						log_error("(line " + std::to_string(index + 1) + ") don't use spaces in key name");
						return result;
					}
				} else if (i == '#') {
					if (key.empty()) {
						skip = true;
						break;
					} else {
						key.push_back(i);
					}
				} else if (i == ':') {
					keyEntering = false;
				} else {
					key.push_back(i);
				}
			} else {
				if (i == ' ' && !quoted) {
					if (!value.empty()) {
						value.push_back(i);
					}
				} else if (i == '\"') {
					if (quoted) {
						if (slashed) {
							value.push_back('\"');
							slashed = false;
						} else {
							break;
						}
					} else {
						quoted = true;
					}
				} else if (i == '\\') {
					if (quoted) {
						if (slashed) {
							value.push_back('\\');
							slashed = false;
						} else {
							slashed = true;
						}
					} else {
						value.push_back(i);
					}
				} else if (i == 'n' && slashed) {
					slashed = false;
					value.push_back('\n');
				} else {
					if (slashed) {
						slashed = false;
					} else {
						value.push_back(i);
					}
				}
			}
		}
		if (skip || keyEntering) {
			continue;
		}

		bool found = false;
		for (field f : settings.fields) {
			if (f.name == key) {
				found = true;
				if (f.type == datatype::BOOL) {
					std::string lowercase = "";
					for (char i : value) {
						lowercase.push_back(std::tolower(i));
					}
					bool c = false;

					if (lowercase == "yes" || lowercase == "true") {
						c = true;
					} else if (lowercase == "no" || lowercase == "false") {
						c = false;
					} else {
						log_error("(line " + std::to_string(index + 1) + ") invalid boolean value");
						return result;
					}

					result.bools[key] = c;
				} else if (f.type == datatype::CHAR) {
					char c = ' ';
					if (value.size() > 0) {
						c = value[0];
					}

					result.chars[key] = c;
				} else if (f.type == datatype::STRING) {
					result.strings[key] = value;
				} else if (f.type == datatype::LONG) {
					long c = 0;
					try {
						c = std::atol(value.c_str());
					} catch (const std::invalid_argument& e) {
						log_error("(line " + std::to_string(index + 1) + ") invalid numberical value");
						return result;
					} catch (const std::out_of_range& e) {
						log_error("(line " + std::to_string(index + 1) + ") too large numberical value");
						return result;
					}
					result.longs[key] = c;
				} else if (f.type == datatype::ULONG) {
					unsigned long c = 0;
					try {
						long v = std::atol(value.c_str());
						if (v < 0) {
							log_error("(line " + std::to_string(index + 1) + ") value can't be less than 0");
							return result;
						}
						c = v;
					} catch (const std::invalid_argument& e) {
						log_error("(line " + std::to_string(index + 1) + ") invalid numberical value");
						return result;
					} catch (const std::out_of_range& e) {
						log_error("(line " + std::to_string(index + 1) + ") too large numberical value");
						return result;
					}
					result.ulongs[key] = c;
				}

				break;
			}
		}

		if (!found) {
			log_error("(line " + std::to_string(index + 1) + ") invalid key");
			return result;
		}
	}

	result.success = true;
	return result;
}

#endif
