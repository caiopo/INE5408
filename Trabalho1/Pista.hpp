#ifndef PISTA_HPP
#define PISTA_HPP

#include "FilaEnc.hpp"
#include "Carro.hpp"
#include "Semaforo.hpp"
#include "Evento.hpp"

class Pista {
protected:
	Direcao direcao;
	FilaEnc<Carro> fila;
	int tamanho = 0, velocidade = 0;

public:
	Pista(Direcao d, int tam, int vel);
	virtual ~Pista() = default;
	void adiciona(Carro c);
	Carro retira();
	bool estaVazia();
	bool moveCarro(Semaforo& semaforo);
};

class Fonte : public Pista {
private:
	int frequenciaFixa = 0, frequenciaVariavel = 0;
	Pista &saidaDir, &saidaReto, &saidaEsq;

public:
	Fonte(Direcao d, int tam, int vel, int fFixa, int fVar,
		Pista& sDir, Pista& sReto, Pista& sEsq);

	void criaCarro();
	bool moveCarro(Semaforo& semaforo);
	EventoCriarCarro proximoEvento(int tempo);
};

class PistaCentro : public Pista {
private:
	Pista &saidaDir, &saidaReto, &saidaEsq;

public:
	PistaCentro(Direcao d, int tam, int vel,
		Pista& sDir, Pista& sReto, Pista& sEsq);
	bool moveCarro(Semaforo& semaforo);
};


class Sumidouro : public Pista {
public:
	Sumidouro(Direcao d, int tam, int vel);
};

#endif  // PISTA_HPP