#ifndef PISTA_HPP
#define PISTA_HPP

#include "FilaEnc.hpp"
#include "Carro.hpp"

class Pista {
private:
	FilaEnc<Carro> fila;
	int tamanho = 0, velocidade = 0;
	int frequenciaFixa = 0, frequenciaVariavel = 0;
	Pista &saidaDir, &saidaReto, &saidaEsq;

public:
	Pista(int tam, int vel, int fFixa, int fVar,
		Pista& sDir, Pista& sReto, Pista& sEsq);
	void adiciona(Carro c);
	Carro retira();
	bool estaVazia();
};

#endif  // PISTA_HPP