#pragma once
#include <string>

#include "terminfo.cpp"
#include "linuxinfo.cpp"
#include "memoryinfo.cpp"
#include "batteryinfo.cpp"
#include "networkinfo.cpp"
#include "gpuinfo.cpp"
#include "cpuinfo.cpp"

// terminfo.cpp
std::pair<unsigned int, unsigned int> get_term_size();
std::pair<unsigned int, unsigned int> get_term_cells();
std::pair<unsigned int, unsigned int> get_pixels_per_cell();
std::string get_term_name();
std::string get_shell_name();
std::string get_shell_version();
std::string get_colors_block(char i, bool spaces);

// linuxinfo.cpp
std::string get_distro_name();
std::string get_linux_version();
std::string get_uptime();
std::string get_uptime_short();

// memoryinfo.cpp
std::string get_total_ram();
std::string get_free_ram();
std::string get_avialable_ram();
std::string get_busy_ram();
std::string get_total_ram_gb();
std::string get_free_ram_gb();
std::string get_avialable_ram_gb();
std::string get_busy_ram_gb();

// batteryinfo.cpp
std::string get_battery_state();
std::string get_battery_charge();

// networkinfo.cpp
std::string get_ip();

// gpuinfo.cpp
std::string get_gpu_model();

// cpuinfo.cpp
std::string get_cpu_model();
unsigned int get_cpu_logical_cores();
unsigned int get_cpu_physical_cores();
