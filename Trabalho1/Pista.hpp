#ifndef PISTA_HPP
#define PISTA_HPP

#include "FilaEnc.hpp"
#include "Carro.hpp"

class Pista {
private:
	FilaEnc<Carro> fila;
	int size = 0;

public:
	explicit Pista(int tam);
	void adiciona(Carro c);
	Carro retira();
	bool estaVazia();
};

#endif  // PISTA_HPP