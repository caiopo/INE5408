#ifndef PISTA_HPP
#define PISTA_HPP

#include "FilaEnc.hpp"
#include "Carro.hpp"
#include "Semaforo.hpp"

class Pista {
protected:
	Direcao direcao;
	FilaEnc<Carro> fila;
	int tamanho = 0, velocidade = 0;

public:
	Pista(Direcao d, int tam, int vel);
	void adiciona(Carro c);
	Carro retira();
	bool estaVazia();
	virtual bool moveCarro(Semaforo& semaforo);
	int tempoParaPercorrer();
};

class Fonte : public Pista {
private:
	int frequenciaFixa = 0, frequenciaVariavel = 0;
	Pista &saidaDir, &saidaReto, &saidaEsq;

public:
	Fonte(Direcao d, int tam, int vel, int fFixa, int fVar,
		Pista& sDir, Pista& sReto, Pista& sEsq);

	void criaCarro();
	virtual bool moveCarro(Semaforo& semaforo);
	int tempoProximoEvento(int tempo);
};

class PistaCentro : public Pista {
private:
	Pista &saidaDir, &saidaReto, &saidaEsq;

public:
	PistaCentro(Direcao d, int tam, int vel,
		Pista& sDir, Pista& sReto, Pista& sEsq);
	virtual bool moveCarro(Semaforo& semaforo);
};

class Sumidouro : public Pista {
public:
	Sumidouro(Direcao d, int tam, int vel);
};

#endif  // PISTA_HPP