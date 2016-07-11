#include "Utils.hpp"
#include "Registro.hpp"
#include "ArvoreAVL.hpp"
#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>

const char* path = "ManPages/";
const char* manpagesfile = "ManPages.dat";

void init();
void read();
void search();


int main() {
	ArvoreAVL<int> avl;

	for (int i = 0; i < 10; ++i) {
		avl.inserir(i);
	}

	auto vec = avl.emOrdem();

	for (auto i = vec.begin(); i != vec.end(); ++i)
		std::cout << *(*i)->getDado() << std::endl;

	avl.saveOnDisk("avltree.dat");
}

// int main(int argc, const char* argv[]) {
// 	if (argc < 2) {
// 		std::cout << "usage: " << argv[0] << " <init|search> [args]" << std::endl;
// 		return 1;
// 	}

// 	if (strcmp(argv[1], "init") == 0) {
// 		init();
// 		return 0;
// 	}

// 	read();

// 	if (strcmp(argv[1], "search") == 0) {

// 	}
// }

void init() {
	auto files = ls(path);

	std::ofstream output(manpagesfile, std::ios::out | std::ios::binary);

	if (!output) {
		throw std::runtime_error("Main::init: could not open file");
	}

	Registro registro;

	for (auto i = files.begin(); i != files.end(); ++i) {

		auto str = readwhole(std::string(path) + *i);

		strcpy(registro.comando, (*i).c_str());
		strcpy(registro.conteudo, str.c_str());

		output.write((char*) &registro, sizeof(Registro));
	}
}

void read() {
	std::ifstream input(manpagesfile, std::ios::in | std::ios::binary);

	if (!input) {
		throw std::runtime_error("Main::read: could not open file");
	}

	Registro registro;

	while (input.good()) {
		input.read((char*) &registro, sizeof(Registro));

		std::cout << registro.comando << std::endl;
		std::cout <<"------------------------------------------"<< std::endl;
		std::cout << registro.conteudo << std::endl << std::endl;
		std::cout <<"------------------------------------------"<< std::endl;

	}

}

void search() {

}