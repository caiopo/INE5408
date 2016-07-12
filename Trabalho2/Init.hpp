#ifndef INDEX_HPP
#define INDEX_HPP

#include "Registro.hpp"
#include "Utils.hpp"
#include "ArvoreAVL.hpp"
#include <fstream>

const std::string PATH = "ManPages/";
const std::string MANPAGES = "ManPages.dat";
const std::string INVERTED_INDEX = "InvertedIndex.dat";

void generateInvertedIndex() {
	ArvoreAVL<Word> wordtree;

	std::ifstream input(MANPAGES, std::ios::in | std::ios::binary);
	std::ofstream output(INVERTED_INDEX, std::ios::out | std::ios::binary);

 	if (!input || !output) {
		throw std::runtime_error("Main::generateInvertedIndex: could not open file");
	}

	Registro registro;
	Word word;

	while (input.good()) {

		input.read((char*) &registro, sizeof(Registro));

		auto wordvec = listOfWords(registro.conteudo);

	}

}

void generateManpages() {
	auto files = ls(PATH);

	std::ofstream output(MANPAGES, std::ios::out | std::ios::binary);

	if (!output) {
		throw std::runtime_error("Main::generateManpagesDat: could not open file");
	}

	Registro registro;

	for (auto i = files.begin(); i != files.end(); ++i) {

		auto str = readwhole(std::string(PATH) + *i);

		strcpy(registro.comando, (*i).c_str());
		strcpy(registro.conteudo, str.c_str());

		output.write((char*) &registro, sizeof(Registro));
	}

	output.close();
}

void init() {
	generateManpages();
	generateInvertedIndex();
}

#endif  // INDEX_HPP