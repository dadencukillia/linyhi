#include "hwinfo/gpu.h"
#include <string>


std::string get_gpu_model() {
	for (hwinfo::GPU gpu : hwinfo::getAllGPUs()) {
		return gpu.name();
	}

	return "";
}
