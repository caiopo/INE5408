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

/**
 * @brief      Operador de inserção em stream do tipo Direcao
 *
 * @param      out   Stream de saida para inserir a direção
 * @param[in]  d     A direção
 *
 * @return     A stream out
 */
std::ostream& operator<<(std::ostream& out, Direcao d);

namespace DirecaoFunc {
	/**
	 * @brief      Retorna a direita de uma direção
	 *
	 * @param[in]  d     A direção escolhida
	 *
	 * @return     A direita de d
	 */
	Direcao getDireita(Direcao d);

	/**
	 * @brief      Retorna a direção oposta a uma direção
	 *
	 * @param[in]  d     A direção escolhida
	 *
	 * @return     O oposto de d
	 */
	Direcao getReto(Direcao d);

	/**
	 * @brief      Retorna a esquerda de uma direção
	 *
	 * @param[in]  d     A direção escolhida
	 *
	 * @return     A esquerda de d
	 */
	Direcao getEsquerda(Direcao d);
}

/**
 * @brief      Classe que representa um semáforo
 */
class Semaforo {
private:
	Direcao direcao = Direcao::NORTE;  // Direção atual
	NumSemaforo num;  // Número do semáforo (S1 ou S2)

public:
	explicit Semaforo(NumSemaforo n);  // Construtor do Semáforo
	void proximoEstado();  // Troca a direção do semáforo para a próxima
	Direcao decideDirecao(Direcao d) const;  // Decide a direção do carro
	                                         // baseada na direção atual,
	                                         // no número do semáforo e nas
	                                         // constantes pré-definidas

	Direcao direcaoAtual();  // Retorna a direção atual
};

#endif  // SEMAFORO_HPP