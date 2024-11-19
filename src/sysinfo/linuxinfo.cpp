#include <cctype>
#include <string>
#include <sys/utsname.h>
#include "../utils/files.cpp"
#include "../utils/command.cpp"
#include "../utils/strings.cpp"

std::string get_distro_name() {
	file_info file = read_file("/etc/os-release");
	if (!file.opened) {
		utsname info;
		if (uname(&info) != 0) {
			return "";
		}

		return std::string(info.nodename);
	}

	file.content.push_back('\n');

	bool keyEntering = true;
	std::string key = "";
	std::string value = "";
	for (char i : file.content) {
		if (i == '\n') {
			if (key == "NAME") {
				return value;
			}

			key = "";
			value = "";
			keyEntering = true;
		} else if (keyEntering) {
			if (i == '=') {
				keyEntering = false;
			} else if (std::isalpha(i) || i == '_' || i == '-') {
				key.push_back(i);
			}
		} else {
			if (std::isalpha(i) || i == ' ') {
				value.push_back(i);
			}
		}
	}

	return "";
}

std::string get_linux_version() {
	utsname info;
	if (uname(&info) != 0) {
		return "";
	}

	return std::string(info.release);
}

std::string get_uptime() {
	file_info file = read_file("/proc/uptime");
	if (!file.opened) {
		return std::string(exec("uptime -p"));
	}

	unsigned long parsed_secs = 0;
	for (char i : file.content) {
		bool breakFor = false;
		switch (i) {
			case '0':
				parsed_secs *= 10;
				break;
			case '1':
				parsed_secs *= 10;
				parsed_secs += 1;
				break;
			case '2':
				parsed_secs *= 10;
				parsed_secs += 2;
				break;
			case '3':
				parsed_secs *= 10;
				parsed_secs += 3;
				break;
			case '4':
				parsed_secs *= 10;
				parsed_secs += 4;
				break;
			case '5':
				parsed_secs *= 10;
				parsed_secs += 5;
				break;
			case '6':
				parsed_secs *= 10;
				parsed_secs += 6;
				break;
			case '7':
				parsed_secs *= 10;
				parsed_secs += 7;
				break;
			case '8':
				parsed_secs *= 10;
				parsed_secs += 8;
				break;
			case '9':
				parsed_secs *= 10;
				parsed_secs += 9;
				break;
			case ' ' | '.':
				breakFor = true;
				break;
		}
		if (breakFor) {
			break;
		}
	}

	return time_seconds_to_human(parsed_secs);
}
