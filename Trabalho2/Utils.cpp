#include "Utils.hpp"
#include <fstream>
#include <memory>
#include <sstream>
#include <iostream>
#include <cstdio>

std::string exec(const char* cmd) {
	char buffer[128];
	std::string result = "";
	std::shared_ptr<FILE> pipe(popen(cmd, "r"), pclose);

	if (!pipe)
		throw std::runtime_error("popen() failed!");

	while (!feof(pipe.get())) {
		if (fgets(buffer, 128, pipe.get()) != NULL)
			result += buffer;
	}

	return result;
}

std::string exec(const std::string cmd) {
	return exec(cmd.c_str());
}

void cat(const std::string filename) {
	std::ifstream input(filename.c_str(), std::ios::in | std::ios::binary);

	std::string line;

	if (input.is_open()) {
		while (getline(input, line)) {
			std::cout << line << '\n';
		}

		input.close();
	} else {
		throw std::runtime_error("Error on Utils::cat: error opening file");
	}
}

std::string readwhole(const std::string filename) {
	std::ifstream input(filename.c_str(), std::ios::in | std::ios::binary);

	std::string line;

	std::stringstream ss;

	if (input.is_open()) {
		while (getline(input, line)) {
			ss << line << '\n';
		}

		input.close();
	} else {
		throw std::runtime_error("Error on Utils::cat: error opening file");
	}

	return ss.str();
}

std::vector<std::string> ls(std::string path) {
	auto ls = exec(std::string("ls ") + path);

	return split(ls, '\n');
}

std::vector<std::string> split(const std::string& str, char delim) {
	std::vector<std::string> elems;
	std::stringstream ss(str);
	std::string item;

	while (getline(ss, item, delim)) {
		elems.push_back(item);
	}

	return elems;
}
