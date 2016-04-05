// Copyright 2016 Caio Pereira Oliveira

#ifndef PILHA_HPP
#define PILHA_HPP

#include <stdexcept>

/**
 * @brief      Implementa uma estrutura de dados do tipo Pilha,
 *			   que organiza os elementos de forma que o último a ser inserido
 *			   é o primeiro a ser retirado (Last In First Out ou LIFO).
 *
 * @tparam     T     Parâmetro genérico de Template
 */
template<typename T>
class Pilha {
 private:
	static const int DEFAULT_SIZE = 10;  // Tamanho padrão caso o parâmetro t
										 // do construtor não seja especificado
	int MAXPILHA; /* Tamanho máximo da pilha, definido na instanciação da classe */
	int _topo; /* Guarda o índice do elemento no topo da pilha */
	T* dados; /* Guarda os dados inseridos na pilha */

 public:
	explicit Pilha<T>(int t = DEFAULT_SIZE);
	void empilha(T dado);
	T desempilha();
	T topo();
	int getPosTopo();
	void limparPilha();
	bool PilhaVazia();
	bool PilhaCheia();
};

/**
 * @brief      Construtor da classe Pilha.
 *
 * @param[in]  t     Tamanho máximo da pilha
 *
 * @tparam     T     Parâmetro genérico de Template
 */
template <typename T>
Pilha<T>::Pilha(int t) {
	MAXPILHA = t;
	dados = new T[t];
	_topo = -1;
}

/**
 * @brief      Insere um novo elemento no topo da pilha.
 *			   Joga a exceção "std::runtime_error" caso a pilha esteja cheia.
 *
 * @param[in]  dado  Elemento para inserir
 *
 * @tparam     T     Parâmetro genérico de Template
 */
template <typename T>
void Pilha<T>::empilha(T dado) {
	if(PilhaCheia())
		throw std::runtime_error("pilha cheia");

	_topo++;
	dados[_topo] = dado;
}

/**
 * @brief      Retira o elemento no topo da pilha e o retorna.
 *			   Joga a exceção "std::runtime_error" caso a pilha esteja vazia.
 *
 * @tparam     T     Parâmetro genérico de Template
 *
 * @return     O elemento que estava no topo da pilha
 */
template <typename T>
T Pilha<T>::desempilha() {
	if(PilhaVazia())
		throw std::runtime_error("pilha vazia");

	_topo--;
	return dados[_topo+1];
}

/**
 * @brief      Olha o elemento no topo da pilha e o retorna, sem retirá-lo.
 *			   Joga a exceção "std::runtime_error" caso a pilha esteja vazia.
 *
 * @tparam     T     Parâmetro genérico de Template
 *
 * @return     O elemento que está no topo da pilha
 */
template <typename T>
T Pilha<T>::topo() {
	if(PilhaVazia())
		throw std::runtime_error("pilha vazia");

	return dados[_topo];
}

/**
 * @brief      Consulta o valor do índice do elemento no topo da pilha,
 * 			   este valor, somado a um corresponde ao tamanho atual da pilha.
 * 			   Joga a exceção "std::runtime_error" caso a pilha esteja vazia.
 *
 * @tparam     T     Parâmetro genérico de Template
 *
 * @return     O valor do índice do elemento no topo da pilha
 */
template <typename T>
int Pilha<T>::getPosTopo() {
	if(_topo == -1)
		throw std::runtime_error("pilha vazia");
	return _topo;
}

/**
 * @brief      Retira todos os elementos da pilha, voltando ao estado de pilha vazia.
 *
 * @tparam     T     Parâmetro genérico de Template
 */
template <typename T>
void Pilha<T>::limparPilha() {
	_topo = -1;
}

/**
 * @brief      Testa se a pilha está cheia.
 *
 * @tparam     T     Parâmetro genérico de Template
 *
 * @return     True caso a pilha esteja cheia, False caso contrário
 */
template <typename T>
bool Pilha<T>::PilhaCheia() {
	return _topo == MAXPILHA-1;
}

/**
 * @brief      Testa se a pilha está vazia.
 *
 * @tparam     T     Parâmetro genérico de Template
 *
 * @return     True caso a pilha esteja vazia, False caso contrário
 */
template <typename T>
bool Pilha<T>::PilhaVazia() {
	return _topo == -1;
}

#endif  // PILHA_HPP
