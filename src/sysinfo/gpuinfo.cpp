#ifndef D_GPUINFO_CPP
#define D_GPUINFO_CPP

#include "hwinfo/gpu.h"
#include <string>


std::string get_gpu_model() {
	for (hwinfo::GPU gpu : hwinfo::getAllGPUs()) {
		return gpu.name();
	}

	return "";
}

#endif
