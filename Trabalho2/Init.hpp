#ifndef INIT_HPP
#define INIT_HPP

#include "Structs.hpp"
#include "Utils.hpp"
#include "NoAVL.hpp"
#include "ArvoreAVL.hpp"
#include "Paths.hpp"
#include <fstream>
#include <set>
#include <cstring>

/**
 * @brief      Adiciona uma nova posicao a uma palavra já existente no arquivo
 *             invertido
 *
 * @param      wordptr  Posicao da palavra no arquivo invertido
 * @param[in]  pos      Posicao para adicionar na palavra
 */
void addPageToWord(WordPtr& wordptr, std::streampos pos) {
	Word word;

	std::ifstream input(INVERTED_INDEX, std::ios::in | std::ios::binary);

	if (!input) {
		throw std::runtime_error("Init::addPageToWord: could not open input file");
	}

	input.seekg(wordptr.pos);

	input.read((char*) &word, sizeof(Word));

	input.close();

	word.add(pos);

	std::ofstream output(INVERTED_INDEX, std::ios::out | std::ios::in  | std::ios::binary);

	if (!output) {
		throw std::runtime_error("Init::addPageToWord: could not open output file");
	}

	output.seekp(wordptr.pos);

	output.write((char*) &word, sizeof(Word));

	output.close();
}

/**
 * @brief      Adiciona uma nova palavra ao arquivo invertido
 *
 * @param      word  Palavra a ser adicionada
 *
 * @return     Posicao que a palavra foi inserida
 */
std::streampos addNewWord(Word& word) {
	std::ofstream output(INVERTED_INDEX, std::ios::out | std::ios::app | std::ios::binary);

	if (!output) {
		throw std::runtime_error("Init::addNewWord: could not open output file");
	}

	auto pos = output.tellp();

	output.write((char*) &word, sizeof(Word));

	output.close();

	return pos;
}

/**
 * @brief      Gera e indexa o arquivo invertido
 */
void generateInvertedIndex() {
	ArvoreAVL<WordPtr> wordtree;

	// create empty file
	std::ofstream output(INVERTED_INDEX, std::ios::out | std::ios::binary);
	output.close();

	std::ifstream input(MANPAGES, std::ios::in | std::ios::binary);

 	if (!input) {
		throw std::runtime_error("Init::generateInvertedIndex: could not open file");
	}

	ManPage manpage;

	std::streampos current_pos;

	int count = 0;

	while (input.good()) {
		if ((count % 100) == 0)
			std::cout << "Current manpage: " << count << std::endl;
		++count;

		current_pos = input.tellg();

		input.read((char*) &manpage, sizeof(ManPage));

		auto wordset = listOfWords(manpage.conteudo);

		for (auto i = wordset.begin(); i != wordset.end(); ++i) {
			WordPtr wordptr;
			WordPtr* wordptrptr;
			bool found = true;

			strcpy(wordptr.word, (*i).c_str());

			try {
				wordptrptr = wordtree.busca(wordptr);
			} catch (std::runtime_error& err) {
				found = false;
			}

			if (found) {
				addPageToWord(*wordptrptr, current_pos);
			} else {
				Word word;
				strcpy(word.word, (*i).c_str());
				word.add(current_pos);

				wordptr.pos = addNewWord(word);

				wordtree.inserir(wordptr);
			}
		}
	}

	input.close();

	wordtree.saveOnDisk(INDEX_TREE);
}

/**
 * @brief      Gera e indexa o ManPages.dat
 */
void generateManpages() {
	auto files = ls(PATH + "*.txt");

	ArvoreAVL<ManPagePtr> mptree;

	std::ofstream output(MANPAGES, std::ios::out | std::ios::binary);

	if (!output) {
		throw std::runtime_error("Init::generateManpages: could not open file");
	}

	ManPage mp;
	ManPagePtr mpptr;

	for (auto i = files.begin(); i != files.end(); ++i) {
		auto str = readwhole(*i);

		auto comando = i->substr(i->find_first_of("/")+1);

		comando = comando.substr(0, comando.find_last_of("."));

		strcpy(mp.comando, comando.c_str());
		strcpy(mp.conteudo, str.c_str());

		strcpy(mpptr.comando, comando.c_str());

		mpptr.pos = output.tellp();

		mptree.inserir(mpptr);

		output.write((char*) &mp, sizeof(ManPage));
	}

	output.close();

	mptree.saveOnDisk(MANPAGES_TREE);
}

void init() {
	std::cout << "Generating ManPages.dat" << std::endl;

	generateManpages();

	std::cout << "Finished ManPages.dat\n";
	std::cout << "Generating InvertedIndex.dat" << std::endl;

	generateInvertedIndex();

	std::cout << "Finished InvertedIndex.dat\n";
}

#endif  // INIT_HPP