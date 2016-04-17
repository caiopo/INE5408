#include "ListaEnc.hpp"
#include <iostream>

#define tam 10
#define offset 1000

int main() {

	ListaEnc<int>* l = new ListaEnc<int>();

	for (int i = 0; i < tam ; i++) {
		l->print();
		l->adiciona(i);
	}

	std::cout << "terminou de adicionar" << std::endl;

	for (int i = 0; i < tam ; i++) {
		std::cout << l->retira() << std::endl;
	}

	std::cout << l->listaVazia() << std::endl;
}

