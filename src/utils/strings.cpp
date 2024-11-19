#ifndef D_STRINGS_CPP
#define D_STRINGS_CPP

#include <cstdlib>
#include <string>
#include <vector>

constexpr long bytesInKbytes = 1000;


std::string repeat_spaces(unsigned int spaces) {
	std::string str;
	str.reserve(spaces);
	for (int i = 0; i < spaces; i++) {
		str.push_back(' ');
	}
	return str;
}

std::vector<std::string> split_string(std::string str, char sep) {
	std::vector<std::string> vec;

	std::string part = "";
	for (char i : str) {
		if (i == sep) {
			vec.push_back(part);
			part = "";
		} else {
			part.push_back(i);
		}
	}
	if (!part.empty()) {
		vec.push_back(part);
	}

	return vec;
}

std::string time_seconds_to_human(unsigned long s) {
	unsigned long minutes = s / 60;
	unsigned long hours = minutes / 60;
	unsigned int days = hours / 24;
	unsigned int seconds = s % 60;
	minutes = minutes % 60;
	hours = hours % 24;

	if (days > 0) {
		return std::to_string(days) + " days, " + std::to_string(hours) + " hours";
	} else if (hours > 0) {
		return std::to_string(hours) + " hours, " + std::to_string(minutes) + " minutes";
	} else if (minutes > 0) {
		return std::to_string(minutes) + " minutes, " + std::to_string(seconds) + " seconds";
	} else {
		return std::to_string(seconds) + " seconds";
	}
}

std::string bytes_to_human(long bytes) {
	long kbytes = bytes / bytesInKbytes;
	long mbytes = kbytes / bytesInKbytes;
	long gbytes = mbytes / bytesInKbytes;
	long tbytes = gbytes / bytesInKbytes;
	bytes = bytes % bytesInKbytes;
	kbytes = kbytes % bytesInKbytes;
	mbytes = mbytes % bytesInKbytes;
	gbytes = gbytes % bytesInKbytes;
	tbytes = tbytes % bytesInKbytes;

	if (tbytes > 0) {
		return std::to_string(tbytes) + "." + std::to_string(gbytes * 10 / bytesInKbytes) + " TB";
	} else if (gbytes > 0) {
		return std::to_string(gbytes) + "." + std::to_string(mbytes * 10 / bytesInKbytes) + " GB";
	} else if (mbytes > 0) {
		return std::to_string(mbytes) + "." + std::to_string(kbytes * 10 / bytesInKbytes) + " MB";
	} else if (kbytes > 0) {
		return std::to_string(kbytes) + "." + std::to_string(bytes * 10 / bytesInKbytes) + " KB";
	} else {
		return std::to_string(bytes) + " B";
	}
}

#endif
