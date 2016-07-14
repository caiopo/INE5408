#ifndef INDEX_HPP
#define INDEX_HPP

#include "Registro.hpp"
#include "Utils.hpp"
#include "NoAVL.hpp"
#include "ArvoreAVL.hpp"
#include <fstream>
#include <set>
#include <cstring>

const std::string PATH = "ManPages/";
const std::string MANPAGES = "ManPages.dat";
const std::string INVERTED_INDEX = "InvertedIndex.dat";
const std::string MANPAGES_TREE = "ManPages.tree";
const std::string INDEX_TREE = "Index.tree";

void addPageToIndex(WordPtr& wordptr, std::streampos pos) {
	Word word;

	std::ifstream input(INVERTED_INDEX, std::ios::in | std::ios::binary);

	if (!input) {
		throw std::runtime_error("Main::addPageToIndex: could not open input file");
	}

	input.seekg(wordptr.pos);

	input.read((char*) &word, sizeof(Word));

	input.close();

	word.add(pos);

	std::ofstream output(INVERTED_INDEX, std::ios::out | std::ios::binary);

	if (!output) {
		throw std::runtime_error("Main::addPageToIndex: could not open output file");
	}

	output.seekp(wordptr.pos);

	output.write((char*) &word, sizeof(Word));

	output.close();
}


std::streampos addNewWordToIndex(Word& word) {

	std::ofstream output(INVERTED_INDEX, std::ios::out | std::ios::app | std::ios::binary);

	if (!output) {
		throw std::runtime_error("Main::addPageToIndex: could not open output file");
	}

	auto pos = output.tellp();

	output.write((char*) &word, sizeof(Word));

	output.close();

	return pos;
}


void generateInvertedIndex() {
	ArvoreAVL<WordPtr> wordtree;

	std::ifstream input(MANPAGES, std::ios::in | std::ios::binary);

 	if (!input) {
		throw std::runtime_error("Main::generateInvertedIndex: could not open file");
	}

	Registro registro;

	std::streampos current_pos;

	while (input.good()) {

		current_pos = input.tellg();

		input.read((char*) &registro, sizeof(Registro));

		auto wordset = listOfWords(registro.conteudo);

		for (auto i = wordset.begin(); i != wordset.end(); ++i) {
			WordPtr wordptr;

			strcpy(wordptr.word, (*i).c_str());

			try {
				wordtree.inserir(wordptr);
			} catch (duplicate_entry_error<WordPtr&> err) {

			}

		}

	}

	input.close();

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