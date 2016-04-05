// Copyright 2016 Caio Pereira Oliveira

#ifndef FILA_HPP
#define FILA_HPP

#include <stdexcept>

/**
 * @brief      Implementa uma estrutura de dados do tipo Fila,
 *			   que organiza os elementos de forma que o primeiro a ser inserido
 *			   é o primeiro a ser retirado (First In First Out ou FIFO).
 *
 * @tparam     T     Parâmetro genérico de Template
 */
template <typename T>
class Fila {
 private:
	static const int DEFAULT_SIZE = 10;  // Tamanho padrão caso o parâmetro t
										 // do construtor não seja especificado
	int MAXFILA; /* Tamanho máximo da pilha, definido na instanciação da classe */
	int inicio; /* Guarda o índice do elemento no inicio da fila */
	int fim; /* Guarda o índice do elemento no final da fila */
	T* dados; /* Guarda os dados inseridos na pilha */

 public:
	explicit Fila(int t = DEFAULT_SIZE);
	void inclui(T dado);
	T retira();
	T ultimo();
	int getUltimo();
	bool filaCheia();
	bool filaVazia();
	void inicializaFila();
};

/**
 * @brief      Construtor da classe Fila.
 *
 * @param[in]  t     Tamanho máximo da fila
 *
 * @tparam     T     Parâmetro genérico de Template
 */
template <typename T>
Fila<T>::Fila(int t) {
	dados = new T[t];
	MAXFILA = t;
	inicio = -1;
	fim = -1;
}

/**
 * @brief      Adiciona um elemento no final da fila.
 *			   Joga a exceção "std::runtime_error" caso a fila esteja cheia.
 *
 * @param[in]  dado  Dado para ser adicionado no final da fila
 *
 * @tparam     T     Parâmetro genérico de Template
 */
template <typename T>
void Fila<T>::inclui(T dado) {
	if (filaCheia())
		throw std::runtime_error("fila cheia");

	fim = (fim+1) % MAXFILA;

	dados[fim] = dado;
}

/**
 * @brief      Retira o elemento no início da fila e o retorna.
 *			   Joga a exceção "std::runtime_error" caso a fila esteja vazia.
 *
 * @tparam     T     Parâmetro genérico de Template
 *
 * @return     O elemento retirado do início da fila
 */
template <typename T>
T Fila<T>::retira() {
	if (filaVazia())
		throw std::runtime_error("fila vazia");

	inicio = (inicio+1) % MAXFILA;

	return dados[inicio];
}

/**
 * @brief      Retorna o elemento no início da fila sem remove-lo. Joga a
 *             exceção "std::runtime_error" caso a fila esteja vazia.
 *
 * @tparam     T     Parâmetro genérico de Template
 *
 * @return     O elemento no final da fila
 */
template <typename T>
T Fila<T>::ultimo() {
	if (filaVazia())
		throw std::runtime_error("fila vazia");
	return dados[fim];
}

/**
 * @brief      Retorna o índice do último elemento da fila. Joga a exceção
 *             "std::runtime_error" caso a fila esteja vazia.
 *
 * @tparam     T     Parâmetro genérico de Template
 *
 * @return     O índice do elemento no final da fila
 */
template <typename T>
int Fila<T>::getUltimo() {
	if (filaVazia())
		throw std::runtime_error("fila vazia");
	else if (fim < inicio)
		return fim + (MAXFILA - inicio) - 1;
	else
		return fim - inicio - 1;
}

/**
 * @brief      Testa se a fila está cheia.
 *
 * @tparam     T     Parâmetro genérico de Template
 *
 * @return     True caso a fila esteja cheia, False caso contrário
 */
template <typename T>
bool Fila<T>::filaCheia() {
	return abs(fim-inicio) == MAXFILA;
}

/**
 * @brief      Testa se a fila está vazia.
 *
 * @tparam     T     Parâmetro genérico de Template
 *
 * @return     True caso a fila esteja vazia, False caso contrário
 */
template <typename T>
bool Fila<T>::filaVazia() {
	return inicio == fim;
}

/**
 * @brief      Limpa a fila, removendo todos os elementos.
 *
 * @tparam     T     Parâmetro genérico de Template
 */
template <typename T>
void Fila<T>::inicializaFila() {
	inicio = -1;
	fim = -1;
}

#endif  // FILA_HPP
