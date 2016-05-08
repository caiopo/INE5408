// Copyright 2016 Caio Pereira Oliveira

#ifndef FILAENC_HPP
#define FILAENC_HPP

#include <memory>
#include <stdexcept>
#include "Elemento.hpp"

/**
 * @brief      Implementa uma estrutura de dados do tipo Fila, que organiza os
 *             elementos de forma que o primeiro a ser inserido é o primeiro a
 *             ser retirado (First In First Out ou FIFO).
 *
 * @tparam     T     Parâmetro de Template
 */
template <typename T>
class FilaEnc {
 private:
	std::shared_ptr<Elemento<T>> head;  // Ponteiro para o primeiro
										// elemento da fila

	std::shared_ptr<Elemento<T>> tail;  // Ponteiro para o último
										// elemento da fila

 public:
	/**
	 * @brief      Construtor da fila. Inicia a fila vazia
	 */
	FilaEnc() = default;

	/**
	 * @brief      Destrutor da fila. Remove todos os elementos para evitar
	 *             vazamento de memória
	 */
	~FilaEnc() {
		limparFila();
	}

	/**
	 * @brief      Adiciona um elemento no final da fila. Joga a exceção
	 *             "std::runtime_error" caso a fila esteja cheia.
	 *
	 * @param[in]  dado  Dado para ser adicionado no final da fila
	 */
	void inclui(const T& dado) {
		if(filaVazia()) {
			head = std::make_shared<Elemento<T>>(dado, nullptr);
			tail = head;
		} else {
			tail->setProximo(std::make_shared<Elemento<T>>(dado, nullptr));
			tail = tail->getProximo();
		}
	}

	/**
	 * @brief      Retira o elemento no início da fila e o retorna. Joga a
	 *             exceção "std::runtime_error" caso a fila esteja vazia.
	 *
	 * @return     O elemento retirado do início da fila
	 */
	T retira() {
		if(filaVazia())
			throw std::runtime_error("fila vazia");

		T retirado = head->getInfo();
		head = head->getProximo();

		return retirado;
	}

	/**
	 * @brief      Retorna o elemento no final da fila sem remove-lo. Joga a
	 *             exceção "std::runtime_error" caso a fila esteja vazia.
	 *
	 * @return     O elemento no final da fila
	 */
	T ultimo() {
		if(filaVazia())
			throw std::runtime_error("fila vazia");

		return tail->getInfo();
	}

	/**
	 * @brief      Retorna o elemento no início da fila sem remove-lo. Joga a
	 *             exceção "std::runtime_error" caso a fila esteja vazia.
	 *
	 * @return     O elemento no início da fila
	 */
	T primeiro() {
		if(filaVazia())
			throw std::runtime_error("fila vazia");

		return head->getInfo();
	}

	/**
	 * @brief      Testa se a fila está vazia.
	 *
	 * @return     True caso a fila esteja vazia, False caso contrário
	 */
	bool filaVazia() {
		return head == nullptr;
	}

	/**
	 * @brief      Limpa a fila, removendo todos os elementos.
	 */
	void limparFila() {
		head = nullptr;
		tail = nullptr;
	}
};

#endif  // FILAENC_HPP
