#ifndef D_LINUXINFO_CPP
#define D_LINUXINFO_CPP

#include <cctype>
#include <string>
#include <sys/utsname.h>
#include <sys/sysinfo.h>
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
	struct sysinfo info;
	if (sysinfo(&info) < 0) {
		return std::string(exec("uptime -p"));
	}

	return time_seconds_to_human(info.uptime);
}

std::string get_uptime_short() {
	struct sysinfo info;
	if (sysinfo(&info) < 0) {
		return std::string(exec("uptime -p"));
	}

	return time_seconds_to_human_short(info.uptime);
}

#endif
