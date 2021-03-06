#include "Semaforo.hpp"
#include <stdexcept>
#include <cstdlib>
#include <iostream>

/**
 * @brief      Retorna a direita de uma direção
 *
 * @param[in]  d     A direção escolhida
 *
 * @return     A direita de d
 */
Direcao DirecaoFunc::getDireita(Direcao d) {
	switch (d) {
	case Direcao::NORTE:
		return Direcao::OESTE;

	case Direcao::SUL:
		return Direcao::LESTE;

	case Direcao::OESTE:
		return Direcao::SUL;

	case Direcao::LESTE:
		return Direcao::NORTE;

	default:
		throw std::logic_error("direcao não encontrada");
	}

	return Direcao::NORTE;
}

/**
 * @brief      Retorna a direção oposta a uma direção
 *
 * @param[in]  d     A direção escolhida
 *
 * @return     O oposto de d
 */
Direcao DirecaoFunc::getReto(Direcao d) {
	switch (d) {
	case Direcao::NORTE:
		return Direcao::SUL;

	case Direcao::SUL:
		return Direcao::NORTE;

	case Direcao::OESTE:
		return Direcao::LESTE;

	case Direcao::LESTE:
		return Direcao::OESTE;

	default:
		throw std::logic_error("direcao não encontrada");
	}

	return Direcao::NORTE;
}

/**
 * @brief      Retorna a esquerda de uma direção
 *
 * @param[in]  d     A direção escolhida
 *
 * @return     A esquerda de d
 */
Direcao DirecaoFunc::getEsquerda(Direcao d) {
	switch (d) {
	case Direcao::NORTE:
		return Direcao::LESTE;

	case Direcao::SUL:
		return Direcao::OESTE;

	case Direcao::OESTE:
		return Direcao::NORTE;

	case Direcao::LESTE:
		return Direcao::SUL;

	default:
		throw std::logic_error("direcao não encontrada");
	}

	return Direcao::NORTE;
}

namespace {

	/**
	 * @brief      Decide a direção que deverá ser virada
	 *
	 * @param[in]  atual     Direção atual
	 * @param[in]  probEsq   Probabilidade de virar a esquerda
	 * @param[in]  probReto  Probabilidade de seguir em frente
	 * @param[in]  probDir   Probabilidade de virar a direita
	 *
	 * @return     A direção que deverá ser virada
	 */
	Direcao random(Direcao atual, int probEsq, int probReto, int probDir) {
		if (probEsq+probReto+probDir != 100)
			throw std::logic_error("");

		int r = rand() % 100;

		if (r < probEsq)
			return DirecaoFunc::getEsquerda(atual);
		else if (r < (probEsq+probReto))
			return DirecaoFunc::getReto(atual);
		else
			return DirecaoFunc::getDireita(atual);
	}
}

/**
 * @brief      Operador de inserção em stream do tipo Direcao
 *
 * @param      out   Stream de saida para inserir a direção
 * @param[in]  d     A direção
 *
 * @return     A stream out
 */
std::ostream& operator<<(std::ostream& out, Direcao d){
	switch(d) {
	case Direcao::NORTE:
		out << "NORTE";
		break;

	case Direcao::LESTE:
		out << "LESTE";
		break;

	case Direcao::SUL:
		out << "SUL";
		break;

	case Direcao::OESTE:
		out << "OESTE";
		break;
	}

	return out;
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

Direcao Semaforo::decideDirecao(Direcao d) const {
	if (num == NumSemaforo::S1) {
		switch (d) {
			case Direcao::NORTE:
				return random(Direcao::NORTE, 80, 10, 10);

			case Direcao::LESTE:
				return random(Direcao::LESTE, 10, 80, 10);

			case Direcao::SUL:
				return random(Direcao::SUL, 10, 10, 80);

			case Direcao::OESTE:
				return random(Direcao::OESTE, 30, 40, 30);

			default:
				throw std::runtime_error("direcao != {NORTE|SUL|LESTE|OESTE}");
		}
	} else {
		switch (d) {
			case Direcao::NORTE:
				return random(Direcao::NORTE, 30, 40, 30);

			case Direcao::LESTE:
				return random(Direcao::LESTE, 40, 30, 30);

			case Direcao::SUL:
				return random(Direcao::SUL, 30, 30, 40);

			case Direcao::OESTE:
				return random(Direcao::OESTE, 30, 30, 40);

			default:
				throw std::runtime_error("direcao != {NORTE|SUL|LESTE|OESTE}");
		}
	}
}

Direcao Semaforo::direcaoAtual() {
	return direcao;
}
