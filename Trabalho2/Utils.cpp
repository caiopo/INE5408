#include "Utils.hpp"
#include <fstream>
#include <memory>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <cstdio>

const std::vector<std::string> conectivos = {
	"and", "that", "but", "or", "as", "if", "when",
	"than", "because", "while", "where", "after", "so",
	"though", "since", "until", "whether", "before",
	"although", "nor", "like", "once", "unless", "now",
	"except", "<->", "a", "the", "of", "to", "into",
	"by", "for", "on", "at", "in", "next", "then", "more",
	"only", "always", "never", "all", "off", "with", "this"
};

const std::string SPECIAL_CHARS = " \n\r\t,.;\"'!@#$%%^&*()[]{}+-/<>?\\`~_:";

std::string exec(const std::string cmd) {
	char buffer[128];
	std::string result = "";
	std::shared_ptr<FILE> pipe(popen(cmd.c_str(), "r"), pclose);

	if (!pipe) {
		throw std::runtime_error("Utils::exec: popen() failed!");
	}

	while (!feof(pipe.get())) {
		if (fgets(buffer, 128, pipe.get()) != NULL)
			result += buffer;
	}

	return result;
}

void cat(const std::string filename) {
	std::ifstream input(filename, std::ios::in | std::ios::binary);

	std::string line;

	if (!input) {
		throw std::runtime_error("Utils::cat: could not open file");
	}

	while (getline(input, line)) {
		std::cout << line << '\n';
	}

	input.close();
}

std::string readwhole(const std::string filename) {
	std::ifstream input(filename, std::ios::in | std::ios::binary);

	std::string line;

	std::stringstream ss;

	if (!input) {
		throw std::runtime_error("Utils::readwhole: could not open file");
	}

	while (getline(input, line)) {
		ss << line << '\n';
	}

	input.close();

	return ss.str();
}

std::vector<std::string> ls(std::string path) {
	auto ls = exec(std::string("ls ") + path);

	return split(ls, "\n");
}

std::vector<std::string> split(const std::string& str, const std::string& delim) {
	std::vector<std::string> words;

	tokenize(str, words, delim);

	return words;
}

void replace_chars(std::string& str, const std::string& to_replace, const char by) {
	for (auto i = to_replace.begin(); i != to_replace.end(); ++i) {
		std::replace(str.begin(), str.end(), *i, by);
	}


}

bool valid_word(std::string& str) {
	// auto found = find(conectivos.begin(), conectivos.end(), str) != conectivos.end();

	bool found = false;

	for (auto i = conectivos.begin(); i != conectivos.end(); ++i) {
		if (*i == str) {
			found = true;
			break;
		}
	}

	return !found && (str.size() > 2);
}

std::vector<std::string> listOfWords(std::string str) {
	std::vector<std::string> valid;

	std::transform(str.begin(), str.end(), str.begin(), ::tolower);

	replace_chars(str, SPECIAL_CHARS);

	std::cout << "------------------------------\n" << str << std::endl << "------------------------------\n";

	auto wordvec = split(str, " ");

	for (auto i = wordvec.begin(); i != wordvec.end(); ++i) {
		if (valid_word(*i)) {
			valid.push_back(*i);
		}
	}

	return wordvec;
}