#ifndef D_COMMAND_CPP
#define D_COMMAND_CPP

#include <cstdio>
#include <memory>
#include <string>
#include <array>

std::string exec(const char* cmd) {
    std::array<char, 128> buffer;
    std::string result;
    std::unique_ptr<FILE, int (*)(FILE*)> pipe(popen(cmd, "r"), pclose);
    if (!pipe) {
		return "";
    }
    while (fgets(buffer.data(), static_cast<int>(buffer.size()), pipe.get()) != nullptr) {
        result += buffer.data();
    }
    return result;
}

#endif
