#ifndef D_FILES_CPP
#define D_FILES_CPP

#include <cstdlib>
#include <ctime>
#include <filesystem>
#include <fstream>
#include <stdexcept>
#include <string>
#include <vector>
#include "color.cpp"

struct image_info {
	bool opened;
	std::vector<char> content;
	unsigned int img_width = 0;
	unsigned int img_height = 0;
};

struct file_info {
	bool opened;
	std::string content;
};

std::string replace_tilde_path(std::string path) {
	std::string home = std::getenv("HOME")?:"";
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

image_info read_image(std::string path) {
	std::string handled_path = replace_tilde_path(path);

	// Opening the file
	std::ifstream file(handled_path);
	if (!file.is_open())
		return image_info{false};

	// Determining size of the file
	file.seekg(0, std::ios::end);
    size_t file_size = file.tellg();
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
	try {
		vec.reserve(std::max<size_t>(10, file_size));
	} catch(std::length_error _) {}

	char byte;
	while (file.get(byte)) {
		vec.push_back(byte);
	}

	file.close();

	return image_info {
		true,
		vec,
		width,
		height
	};
}

file_info read_file(std::string path) {
	std::string handled_path = replace_tilde_path(path);

	// Opening the file
	std::ifstream file(handled_path);
	if (!file.is_open())
		return file_info{false};

	// Determining size of the file
	file.seekg(0, std::ios::end);
    size_t file_size = file.tellg();
    file.seekg(0, std::ios::beg);

	// Writing data in the new string
	std::string str;
	try {
		str.reserve(std::max<size_t>(10, file_size));
	} catch(std::length_error _) {}

	char byte;
	while (file.get(byte)) {
		str.push_back(byte);
	}

	file.close();

	return file_info {
		true,
		str,
	};
}

std::string get_random_file_from_directory(std::string dirpath) {
	srand(time(NULL));
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

	return files[rand() % files.size()];
}

#endif
