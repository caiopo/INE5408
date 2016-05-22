#ifndef SEMAFORO_HPP
#define SEMAFORO_HPP
#include <iostream>

enum class Direcao {
	NORTE,
	SUL,
	LESTE,
	OESTE
};

enum class NumSemaforo {
	S1,
	S2
};

std::ostream& operator<<(std::ostream& out, Direcao d);

namespace DirecaoFunc {
	Direcao getDireita(Direcao d);
	Direcao getReto(Direcao d);
	Direcao getEsquerda(Direcao d);
}

class Semaforo {
private:
	Direcao direcao = Direcao::NORTE;
	NumSemaforo num;

public:
	explicit Semaforo(NumSemaforo n);
	void proximoEstado();
	Direcao decideDirecao(Direcao d) const;
	bool estaAberto();
	Direcao direcaoAtual();
};

#endif  // SEMAFORO_HPP