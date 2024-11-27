#ifndef D_MEMORYINFO_CPP
#define D_MEMORYINFO_CPP

#include "hwinfo/ram.h"
#include "../utils/strings.cpp"
#include <string>

std::string get_total_ram() {
	hwinfo::Memory memory;
	return bytes_to_human(memory.total_Bytes());
}

std::string get_free_ram() {
	hwinfo::Memory memory;
	return bytes_to_human(memory.free_Bytes());
}

std::string get_avialable_ram() {
	hwinfo::Memory memory;
	return bytes_to_human(memory.available_Bytes());
}

std::string get_busy_ram() {
	hwinfo::Memory memory;
	return bytes_to_human(memory.total_Bytes() - memory.available_Bytes());
}

std::string get_total_ram_gb() {
	hwinfo::Memory memory;
	long bytes = memory.total_Bytes();
	long mbytes = bytes / bytesInKbytes / bytesInKbytes;
	long gbytes = mbytes / bytesInKbytes;
	return std::to_string(gbytes % bytes) + "." + std::to_string(mbytes % bytesInKbytes * 10 / bytesInKbytes);
}

std::string get_free_ram_gb() {
	hwinfo::Memory memory;
	long bytes = memory.free_Bytes();
	long mbytes = bytes / bytesInKbytes / bytesInKbytes;
	long gbytes = mbytes / bytesInKbytes;
	return std::to_string(gbytes % bytes) + "." + std::to_string(mbytes % bytesInKbytes * 10 / bytesInKbytes);
}

std::string get_avialable_ram_gb() {
	hwinfo::Memory memory;
	long bytes = memory.available_Bytes();
	long mbytes = bytes / bytesInKbytes / bytesInKbytes;
	long gbytes = mbytes / bytesInKbytes;
	return std::to_string(gbytes % bytes) + "." + std::to_string(mbytes % bytesInKbytes * 10 / bytesInKbytes);
}

std::string get_busy_ram_gb() {
	hwinfo::Memory memory;
	long bytes = memory.total_Bytes() - memory.available_Bytes();
	long mbytes = bytes / bytesInKbytes / bytesInKbytes;
	long gbytes = mbytes / bytesInKbytes;
	return std::to_string(gbytes % bytes) + "." + std::to_string(mbytes % bytesInKbytes * 10 / bytesInKbytes);
}

#endif
