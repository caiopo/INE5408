#include "Utils.hpp"
#include "ArvoreAVL.hpp"
#include "Init.hpp"
#include "Search.hpp"
#include <iostream>
#include <cstring>

void usage(const char* argv) {
	std::cout << "usage: " << argv << " <init|search> [args]" << std::endl;
	exit(1);
}

int main(int argc, const char* argv[]) {
	if (argc < 2) {
		usage(argv[0]);
	}

	if (!strcmp(argv[1], "init")) {
		init();
		return 0;
	}

	if (!strcmp(argv[1], "command")) {
		Searcher::getInstance().byCommand(argv[2]);
		return 0;
	}

	if (!strcmp(argv[1], "term")) {
		// std::vector<std::string> strvec;

		// Searcher::getInstance().byWords(argv[2]);
		return 0;
	}

	usage(argv[0]);
}
