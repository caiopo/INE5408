#include <cstdlib>
#include <stdexcept>
#include "Semaforo.hpp"


namespace {
	Direcao random(Direcao atual, int prob0, int prob1, int prob2) {
		int r = rand() % 100;

		if (r < prob0)
			return 0;
		else if (r < (prob0+prob1))
			return 1;
		else
			return 2;

	}
}

Semaforo::Semaforo(NumSemaforo n) : num(n) {}

void Semaforo::proximoEstado() {
	switch (direcao) {
		case Direcao::NORTE:
			direcao = Direcao::LESTE;
			break;
		case Direcao::LESTE:
			direcao = Direcao::SUL;
			break;
		case Direcao::SUL:
			direcao = Direcao::OESTE;
			break;
		case Direcao::OESTE:
			direcao = Direcao::NORTE;
			break;
	}
}

Direcao Semaforo::decidePista(Direcao d) {
	if (num == NumSemaforo::S1)
		switch (direcao) {
			case Direcao::NORTE:

				break;
			case Direcao::LESTE:

				break;
			case Direcao::SUL:

				break;
			case Direcao::OESTE:

				break;
			default:
				throw std::runtime_error("direcao != {NORTE|SUL|LESTE|OESTE}")
		}
	else
		switch (direcao) {
			case Direcao::NORTE:

				break;
			case Direcao::LESTE:

				break;
			case Direcao::SUL:

				break;
			case Direcao::OESTE:

				break;
			default:
				throw std::runtime_error("direcao != {NORTE|SUL|LESTE|OESTE}")
		}
}
