#include "Utils.hpp"
#include "ArvoreAVL.hpp"
#include "Init.hpp"
#include <iostream>
#include <cstring>

int main(int argc, const char* argv[]) {
	// ArvoreAVL<WordPtr> wordtree;


	// WordPtr a, b, c, d, e, f;

	// strcpy(a.word, "a");
	// strcpy(b.word, "b");
	// strcpy(c.word, "c");
	// strcpy(d.word, "d");
	// strcpy(e.word, "e");
	// strcpy(f.word, "f");

	// wordtree.inserir(a);
	// wordtree.inserir(b);
	// wordtree.inserir(c);
	// wordtree.inserir(d);
	// wordtree.inserir(e);
	// wordtree.inserir(f);

	// WordPtr x;

	// strcpy(x.word, "a");


	// wordtree.busca(x);


	// return 0;


	if (argc < 2) {
		std::cout << "usage: " << argv[0] << " <init|search> [args]" << std::endl;
		return 1;
	}

	if (!strcmp(argv[1], "init")) {
		init();
		return 0;
	}

	if (!strcmp(argv[1], "search")) {
		// TODO
	}
}


/*
int main(int argc, const char* argv[]) {

	srand(time(NULL));

	if (strcmp(argv[1], "write") == 0) {

		ArvoreAVL<int> avl;

		for (int i = 0; i < 10; ++i) {
			avl.inserir(rand());
		}

		auto vec = avl.emOrdem();

		std::cout << vec.size() << std::endl;

		for (auto i = vec.begin(); i != vec.end(); ++i)
			std::cout << *(*i)->getDado() << " ";

		std::cout << std::endl;

		avl.saveOnDisk("avltree.dat");

	} else {
		ArvoreAVL<int> avl("avltree.dat");

		std::cout << vec.size() << std::endl;

		for (auto i = vec.begin(); i != vec.end(); ++i)
			std::cout << *(*i)->getDado() << " ";

		std::cout << std::endl;

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

	input.close();

}

*/
