#include "hwinfo/battery.h"
#include <string>

std::string get_battery_state() {
	hwinfo::Battery battery;
	if (battery.charging()) {
		return "charging";
	} else {
		return "discharging";
	}
}

std::string get_battery_charge() {
	hwinfo::Battery battery;
	return std::to_string(int(battery.capacity() * 100));
}
