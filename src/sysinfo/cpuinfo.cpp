#include "hwinfo/cpu.h"
#include <string>


std::string get_cpu_model() {
	for (hwinfo::CPU cpu : hwinfo::getAllCPUs()) {
		return cpu.modelName();
	}

	return "";
}

unsigned int get_cpu_logical_cores() {
	for (hwinfo::CPU cpu : hwinfo::getAllCPUs()) {
		return cpu.numLogicalCores();
	}

	return 0;
}

unsigned int get_cpu_physical_cores() {
	for (hwinfo::CPU cpu : hwinfo::getAllCPUs()) {
		return cpu.numPhysicalCores();
	}

	return 0;
}
