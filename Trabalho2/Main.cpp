#include "Utils.hpp"
#include "ArvoreAVL.hpp"
#include "Init.hpp"
#include <iostream>
#include <cstring>

void search();

int main(int argc, const char* argv[]) {
	std::string teste = "<beginning of page>"
"atan, atanf, atanl <-> arc tangent function"
"c99 [ flag... ] file... -lm [ library... ]"
"#include <math.h>"
"double atan(double x);"
"float atanf(float x);"
"long double atanl(long double x);"
"These functions compute the principal value of the arc tangent of x."
"Upon successful completion, these functions return the arc tangent of x in the range [<mi><*p> /2,<*p> /2] radians."
"If x is NaN, NaN is returned."
"If x is <+->0, x is returned."
"If x is <+->Inf, <+-><*p> /2 is returned."
"No errors are defined."
"See attributes(5) for descriptions of the following attributes:"
"tab() box; cw(2.75i) |cw(2.75i) lw(2.75i) |lw(2.75i) ATTRIBUTE TYPEATTRIBUTE VALUE _ Interface Stability<hy>"
"Standard _ MT-LevelMT-Safe"
"atan2(3M), isnan(3M), math.h(3HEAD), tan(3M), attributes(5), standards(5)";


	auto vec = listOfWords(teste);

	for (auto i = vec.begin(); i != vec.end(); ++i) {
		std::cout << "\"" << *i << "\"" << std::endl;
	}

	return 0;

	if (argc < 2) {
		std::cout << "usage: " << argv[0] << " <init|search> [args]" << std::endl;
		return 1;
	}

	if (!strcmp(argv[1], "init")) {
		init();
		return 0;
	}

	if (!strcmp(argv[1], "search")) {

	}
}

void search() {


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
