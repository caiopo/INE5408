// Copyright 2016 Caio Pereira Oliveira

#ifndef PILHAENC_HPP
#define PILHAENC_HPP

#include <memory>
#include <stdexcept>
#include "Elemento.hpp"

/**
 * @brief      Implementa uma Pilha Encadeada que organiza os elementos de forma
 *             que o último a ser inserido é o primeiro a ser retirado (Last In
 *             First Out ou LIFO).
 *
 * @tparam     T     Parâmetro de Template
 */
template<typename T>
class PilhaEnc {
 private:
	std::shared_ptr<Elemento<T>> head;  // Ponteiro para o
										// primeiro elemento da pilha

 public:
 	/**
	 * @brief      Construtor da pilha. Inicia a pilha vazia
	 */
	PilhaEnc() = default;

	/**
	 * @brief      Destrutor da pilha. Remove todos os elementos para evitar
	 *             vazamento de memória
	 */
	~PilhaEnc() {
		head = nullptr;
	}

	/**
	 * @brief      Insere um novo elemento no topo da pilha.
	 *
	 * @param[in]  dado  Elemento para inserir
	 */
	void empilha(const T& dado) {
		head = std::make_shared<Elemento<T>>(dado, head);
	}


	/**
	 * @brief      Retira o elemento no topo da pilha e o retorna. Joga a
	 *             exceção "std::runtime_error" caso a pilha esteja vazia.
	 *
	 * @return     O elemento que estava no topo da pilha
	 */
	T desempilha() {
		if(PilhaVazia())
			throw std::runtime_error("fila vazia");

		T removido = head->getInfo();
		head = head->getProximo();
		return removido;
	}

	/**
	 * @brief      Olha o elemento no topo da pilha e o retorna, sem retirá-lo.
	 *             Joga a exceção "std::runtime_error" caso a pilha esteja
	 *             vazia.
	 *
	 * @return     O elemento que está no topo da pilha
	 */
	T topo() {
		if(PilhaVazia())
			throw std::runtime_error("fila vazia");

		return head->getInfo();
	}

	/**
	 * @brief      Retira todos os elementos da pilha, voltando ao estado de
	 *             pilha vazia.
	 */
	void limparPilha() {
		head = nullptr;
	}

	/**
	 * @brief      Testa se a pilha está vazia.
	 *
	 * @return     True caso a pilha esteja vazia, False caso contrário
	 */
	bool PilhaVazia() {
		return head == nullptr;
	}
};

#endif  // PILHAENC_HPP
