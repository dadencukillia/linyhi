#ifndef D_FILES_CPP
#define D_FILES_CPP

#include <chrono>
#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <vector>

struct fileInfo {
	bool opened;
	std::vector<char> content;
	unsigned int img_width = 0;
	unsigned int img_height = 0;
};

std::string replace_tilde_path(std::string path) {
	std::string home = std::getenv("HOME");
	std::string to_return = "";
	to_return.reserve(path.length());
	for (char i : path) {
		if (i == '~') {
			to_return.append(home);
		} else {
			to_return.push_back(i);
		}
	}

	return to_return;
}

fileInfo read_file(std::string path) {
	std::string handled_path = replace_tilde_path(path);

	// Opening the file
	std::ifstream file(handled_path);
	if (!file.is_open())
		return fileInfo{false};

	// Determining size of the file
	file.seekg(0, std::ios::end);
    size_t fileSize = file.tellg();
    file.seekg(0, std::ios::beg);

	// Determining dimension of the image file
	unsigned int width, height = 0;
	unsigned char buf[8];
            
	file.seekg(16);
	file.read(reinterpret_cast<char*>(&buf), 8);

	width = (buf[0] << 24) + (buf[1] << 16) + (buf[2] << 8) + (buf[3] << 0);
	height = (buf[4] << 24) + (buf[5] << 16) + (buf[6] << 8) + (buf[7] << 0);
	file.clear();
	file.seekg(0);

	// Writing data in the new vector
	std::vector<char> vec;
	vec.reserve(fileSize);

	char byte;
	while (file.get(byte)) {
		vec.push_back(byte);
	}

	return fileInfo {
		true,
		vec,
		width,
		height
	};
}

std::string get_random_file_from_directory(std::string dirpath) {
	if (!std::filesystem::is_directory(dirpath)) {
		log_error("image files directory doesn't exist");
		return "";
	}

	std::vector<std::string> files;
	for (const auto &entry : std::filesystem::directory_iterator(dirpath)) {
		if (entry.is_regular_file()) {
			files.push_back(entry.path());
		}
	}

	if (files.empty()) {
		log_error("no image files in the directory");
		return "";
	}

	unsigned long number = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now().time_since_epoch()).count();	
	return files[number % files.size()];
}

#endif
