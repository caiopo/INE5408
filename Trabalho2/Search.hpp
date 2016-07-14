#ifndef SEARCH_HPP
#define SEARCH_HPP

#include "Paths.hpp"
#include "ArvoreAVL.hpp"
#include "Registro.hpp"

class Searcher {
 private:
	ArvoreAVL<WordPtr> wordtree{INDEX_TREE};
	ArvoreAVL<ManPagePtr> mptree{MANPAGES_TREE};

	Searcher() = default;
public:
	~Searcher() = default;
	Searcher(Searcher const&) = delete;
	void operator=(Searcher const&)  = delete;

	static Searcher& getInstance() {
		static Searcher instance;

		return instance;
	}

	void byCommand(std::string str) {
		ManPagePtr mpptr;
		ManPagePtr* mpptrptr;

		strcpy(mpptr.comando, str.c_str());

		try {

			mpptrptr = mptree.busca(mpptr);

		} catch (std::runtime_error&) {
			std::cout << "Command not found" << std::endl;
			return;
		}

		std::ifstream input(MANPAGES, std::ios::in | std::ios::binary);

		if (!input) {
			throw std::runtime_error("Searcher::byCommand: could not open input file");
		}

		input.seekg(mpptrptr->pos);

		ManPage mp;

		input.read((char*) &mp, sizeof(ManPage));

		input.close();

		std::cout << mp.comando << std::endl;
		std::cout << mp.conteudo << std::endl;
	}

	void byWord(std::vector<std::string> strvec) {

	}
};

#endif  // SEARCH_HPP
