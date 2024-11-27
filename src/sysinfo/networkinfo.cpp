#ifndef D_NETWORKINFO_CPP
#define D_NETWORKINFO_CPP

#include "hwinfo/network.h"
#include <string>

std::string get_ip() {
	std::string last_ip6 = "";
	for (hwinfo::Network network : hwinfo::getAllNetworks()) {
		std::string ip4 = network.ip4();
		if (!ip4.empty() && ip4 != "<unknown>" && ip4.rfind("192.168.", 0) == 0) {
			return ip4;
		}

		std::string ip6 = network.ip6();
		if (!ip6.empty() && ip6 != "<unknown>") {
			last_ip6 = ip6;
		}
	}

	return last_ip6;
}

#endif
