#ifndef SEARCH_HPP
#define SEARCH_HPP

#include "Paths.hpp"
#include "ArvoreAVL.hpp"
#include "Structs.hpp"
#include <fstream>
#include <iostream>
#include <algorithm>
#include <set>


/**
 * @brief      Imprime uma manpage de acordo com sua posicao
 *
 * @param[in]  pos   A posicao da manpage
 */
void printFromManpages(std::streampos pos, bool printContent = false) {
	std::ifstream input(MANPAGES, std::ios::in | std::ios::binary);

	if (!input) {
		throw std::runtime_error("Search::printFromManpages: could not open input file");
	}

	input.seekg(pos);

	ManPage mp;

	input.read((char*) &mp, sizeof(ManPage));

	input.close();

	std::cout << "Comando: " << mp.comando << std::endl;

	if (printContent) {
		std::cout << std::endl  << "Conteudo: " << std::endl;
		std::cout << mp.conteudo << std::endl;
	}
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

		printFromManpages(mpptrptr->pos, true);

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

		int nfound = 0;

		if (wordvec.size() == 2) {
			for (unsigned int i = 0; i < wordvec[0].index ; ++i) {
				for (unsigned int j = 0; j < wordvec[1].index ; ++j) {
					if (wordvec[0].pos[i] == wordvec[1].pos[j]) {
						printFromManpages(wordvec[0].pos[i]);
						++nfound;
					}
				}
			}

		} else {
			std::vector<std::streampos> posvec;

			for (auto i = wordvec.begin(); i != wordvec.end(); ++i) {
				for (unsigned int j = 0; j < i->index; ++j) {
					posvec.push_back(i->pos[j]);
				}
			}

			start: for (auto i = posvec.begin(); i != posvec.end(); ++i) {
				if (std::count(posvec.begin(), posvec.end(), *i) == unsigned(wordvec.size())) {
					printFromManpages(*i);
					++nfound;
					posvec.erase(std::remove(posvec.begin(), posvec.end(), *i), posvec.end());
					goto start;
				}
			}
		}

		std::cout << nfound << " manpages found" << std::endl;
	}

	/**
	 * @brief      Pesquisa por palavra de forma disjuntiva
	 *
	 * @param[in]  strvec  Palavras
	 */
	void byWordDisjunctive(std::vector<std::string> strvec) {
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
				continue;
			}

			wordptrvec.push_back(*wordptrptr);
		}

		if (!wordptrvec.size()) {
			std::cout << "0 manpages found" << std::endl;
			return;
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

		std::set<std::streampos> posset;

		for (auto i = wordvec.begin(); i != wordvec.end(); ++i) {
			for (unsigned int j = 0; j < i->index; ++j) {
				posset.insert(i->pos[j]);
			}
		}

		for (auto i = posset.begin(); i != posset.end(); ++i) {
			printFromManpages(*i);
		}

		std::cout << posset.size() << " manpages found" << std::endl;
	}

};

#endif  // SEARCH_HPP
