#include <iostream>
#include <vector>
#include "base64.h"

void draw_png(std::vector<char> data) {
	if (data.size() == 0)
		return;

	// Turning vector to list
	unsigned char *buffer = new unsigned char[data.size()];
	for (unsigned long i = 0; i < data.size(); i++) {
		buffer[i] = data.at(i);
	}

	// Encoding to base64
	std::string b64 = base64_encode(buffer, data.size());

	delete[] buffer;

	// Kitty Protocol
	int chunk_size = 2048;
	int chunks = (b64.length() + chunk_size - 1) / chunk_size;

	printf("\e_Ga=T,f=100,C=1,m=%d;%s\e\\", chunks == 1 ? 0 : 1, b64.substr(0, chunk_size).c_str());

	for (int i = 1; i < chunks; i++) {
		std::string substr = b64.substr(i * chunk_size, chunk_size);
		printf("\e_Gm=%d;%s\e\\", i == chunks - 1 ? 0 : 1, substr.c_str());
	}
	std::cout.flush();
}
