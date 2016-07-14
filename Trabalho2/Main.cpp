#include "Utils.hpp"
#include "ArvoreAVL.hpp"
#include "Init.hpp"
#include "Search.hpp"
#include <iostream>
#include <cstring>

void usage(const char* argv) {
	std::cout << "usage: " << argv << " <init|command|word> [args]" << std::endl;
	std::cout << "init    - indexes the manpages"                   << std::endl;
	std::cout << "command - search by command"                      << std::endl;
	std::cout << "word    - search by word (case insensitive)"      << std::endl;

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

	if (!strcmp(argv[1], "word")) {
		std::vector<std::string> strvec;

		int aux = 2;

		while (aux < argc) {
			strvec.push_back(argv[aux++]);
		}

		Searcher::getInstance().byWord(strvec);
		return 0;
	}

	usage(argv[0]);
}
