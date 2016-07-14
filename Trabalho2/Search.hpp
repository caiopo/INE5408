#ifndef SEARCH_HPP
#define SEARCH_HPP

#include "Paths.hpp"
#include "ArvoreAVL.hpp"
#include "Structs.hpp"
#include <fstream>
#include <iostream>
#include <algorithm>

/**
 * @brief      Imprime uma manpage de acordo com sua posicao
 *
 * @param[in]  pos   A posicao da manpage
 */
void printFromManpages(std::streampos pos) {
	std::ifstream input(MANPAGES, std::ios::in | std::ios::binary);

	if (!input) {
		throw std::runtime_error("Search::printFromManpages: could not open input file");
	}

	input.seekg(pos);

	ManPage mp;

	input.read((char*) &mp, sizeof(ManPage));

	input.close();

	std::cout << "Comando: " << mp.comando << std::endl << std::endl;
	std::cout << "Conteudo: " << std::endl;
	std::cout << mp.conteudo << std::endl;
}

/**
 * @brief      Singleton que serve pra pesquisar palavras e comandos
 */
class Searcher {
 private:
	ArvoreAVL<WordPtr> wordtree{INDEX_TREE};      //! Arvore de WordPtr
	ArvoreAVL<ManPagePtr> mptree{MANPAGES_TREE};  //! Arvore de ManPagePtr

	Searcher() = default;
 public:
	~Searcher() = default;
	Searcher(Searcher const&) = delete;
	void operator=(Searcher const&)  = delete;

	static Searcher& getInstance() {
		static Searcher instance;

		return instance;
	}

	/**
	 * @brief      Pesquisa por comando
	 *
	 * @param[in]  str   Comando
	 */
	void byCommand(std::string str) {
		ManPagePtr mpptr;
		ManPagePtr* mpptrptr;

		strcpy(mpptr.comando, str.c_str());

		try {

			mpptrptr = mptree.busca(mpptr);

		} catch (std::runtime_error&) {
			std::cout << "Command \"" << str << "\"not found" << std::endl;
			return;
		}

		printFromManpages(mpptrptr->pos);

	}

	/**
	 * @brief      Pesquisa por palavra
	 *
	 * @param[in]  strvec  Palavras
	 */
	void byWord(std::vector<std::string> strvec) {
		std::vector<WordPtr> wordptrvec;

		for (auto i = strvec.begin(); i != strvec.end(); ++i) {
			WordPtr wordptr;
			WordPtr* wordptrptr;

			std::transform(i->begin(), i->end(), i->begin(), ::tolower);

			strcpy(wordptr.word, i->c_str());

			try {

				wordptrptr = wordtree.busca(wordptr);

			} catch (std::runtime_error&) {
				std::cout << "Word \"" << *i << "\" not found" << std::endl;
				return;
			}

			wordptrvec.push_back(*wordptrptr);
		}

		std::vector<Word> wordvec;
		Word word;

		std::ifstream input(INVERTED_INDEX, std::ios::in | std::ios::binary);

		if (!input) {
			throw std::runtime_error("Searcher::byWord: could not open input file");
		}

		for (auto i = wordptrvec.begin(); i != wordptrvec.end(); ++i) {
			input.seekg(i->pos);

			input.read((char*) &word, sizeof(Word));
			wordvec.push_back(word);
		}

		input.close();

		std::vector<std::streampos> posvec;

		for (auto i = wordvec.begin(); i != wordvec.end(); ++i) {
			for (unsigned int j = 0; j < i->index; ++j) {
				posvec.push_back(i->pos[j]);
			}
		}

		#define GOTOS_CAN_BE_USEFUL
		#ifdef GOTOS_CAN_BE_USEFUL

		start: for (auto i = posvec.begin(); i != posvec.end(); ++i) {
			if (std::count(posvec.begin(), posvec.end(), *i) == unsigned(wordvec.size())) {
				printFromManpages(*i);
				posvec.erase(std::remove(posvec.begin(), posvec.end(), *i), posvec.end());
				goto start;
			}
		}

		#else

		bool done = false;

		while (!done) {
			done = true;
			for (auto i = posvec.begin(); i != posvec.end(); ++i) {
				if (std::count(posvec.begin(), posvec.end(), *i) == unsigned(wordvec.size())) {
					printFromManpages(*i);
					posvec.erase(std::remove(posvec.begin(), posvec.end(), *i), posvec.end());
					done = false;
					break;
				}
			}
		}

		#endif
	}
};

#endif  // SEARCH_HPP