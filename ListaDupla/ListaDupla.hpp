// Copyright 2016 Caio Pereira Oliveira

#ifndef LISTADUPLA_HPP
#define LISTADUPLA_HPP

#include <memory>
#include <stdexcept>

#include "Elemento.hpp"

/**
 * @brief      Implementa uma Lista Duplamente Encadeada, onde cada elemento tem
 *             um ponteiro para o próximo elemento e para o elemento anterior
 *
 * @tparam     T     Parâmetro de Template
 */
template<typename T>
class ListaDupla {
 private:
	std::shared_ptr<Elemento<T>> head;  // Ponteiro para o
										// primeiro elemento da Lista

	std::shared_ptr<Elemento<T>> tail;  // Ponteiro para o
										// primeiro elemento da Lista

	int size = 0;						// Tamanho da lista

 public:
	/**
	 * @brief      Construtor da lista. Inicia a lista vazia
	 */
	ListaDupla() = default;

	/**
	 * @brief      Destrutor da lista. Deleta todos os elementos para impedir
	 *             vazamento de memória
	 */
	~ListaDupla() {
		destroiListaDuplo();
	}

	/**
	 * @brief      Adiciona um dado no inicio da lista, tornando-o o novo head,
	 *             se a lista estiver vazia, se torna o novo tail também
	 *
	 * @param[in]  dado  Dado a ser adicionado
	 */
	void adicionaNoInicioDuplo(const T& dado) {
		head = std::make_shared<Elemento<T>>(dado, nullptr, head);

		if (listaVazia())
			tail = head;

		++size;
	}

	/**
	 * @brief      Retira o dado armazenado no head e o retorna o novo head passa a ser head->getProximo()
	 *
	 * @return     Dado removido
	 */
	T retiraDoInicioDuplo() {
		if (listaVazia())
			throw std::runtime_error("lista vazia");

		T dado = head->getInfo();

		head = head->getProximo();

		--size;

		return dado;
	}

	/**
	 * @brief      Deleta o elemento no head, destruindo o dado junto
	 */
	void eliminaDoInicioDuplo() {
		if (listaVazia())
			throw std::runtime_error("lista vazia");

		head = head->getProximo();
		--size;
	}

	/**
	 * @brief      Adiciona o dado na posição
	 *
	 * @param[in]  dado  Dado a ser inserido
	 * @param[in]  pos   Posição para inserir o dado
	 */
	void adicionaNaPosicaoDuplo(const T& dado, int pos) {
		if (pos == 0)
			return adicionaNoInicioDuplo(dado);

		if (pos == size)
			return adicionaDuplo(dado);

		auto e = getPtr(pos);

		auto novo = std::make_shared<Elemento<T>>(dado, e->getAnterior(), e);
		e->setAnterior(novo);
		novo->getAnterior()->setProximo(novo);

		++size;
	}

	/**
	 * @brief      Retorna a menor posição na qual o dado esteja
	 *
	 * @param[in]  dado  Dado a ser procurado
	 *
	 * @return     Menor índice do dado na lista
	 */
	int posicaoDuplo(const T& dado) const {
		if (listaVazia())
			throw std::runtime_error("lista vazia");

		auto e = head;

		for (int i = 0; i < size; ++i) {
			if (e->getInfo() == dado)
				return i;
			e = e->getProximo();
		}

		throw std::runtime_error("dado não encontrado");
	}

	/**
	 * @brief      Retorna o ponteiro para o dado armazenado na lista
	 *
	 * @param[in]  dado  Dado para procurar
	 *
	 * @return     Ponteiro para o dado armazenado na lista
	 */
	T* posicaoMemDuplo(const T& dado) const {
		if (listaVazia())
			throw std::runtime_error("lista vazia");

		for (auto e = head; e->getProximo() != nullptr; e = e->getProximo())
			if (e->getInfo() == dado)
				return &e->getInfo();
	}

	/**
	 * @brief      Testa se o dado está na lista
	 *
	 * @param[in]  dado  Dado a ser testato
	 *
	 * @return     true se o dado estiver na lista, senão, false
	 */
	bool contemDuplo(const T& dado) {
		try {
			posicaoDuplo(dado);
		} catch (std::runtime_error& e) {
			return false;
		}

		return true;
	}

	/**
	 * @brief      Retira o dado na posição pos e o retorna
	 *
	 * @param[in]  pos   Posição para retirar
	 *
	 * @return     O dado retirado
	 */
	T retiraDaPosicaoDuplo(int pos) {
		if (pos == 0)
			return retiraDoInicioDuplo();

		if (pos == size)
			return retiraDuplo();

		auto e = getPtr(pos);

		T data = e->getInfo();

		e->getProximo()->setAnterior(e->getAnterior());
		e->getAnterior()->setProximo(e->getProximo());

		--size;

		return data;
	}

	/**
	 * @brief      Adiciona o dado no final da lista
	 *
	 * @param[in]  dado   Dado a ser adicionado
	 */
	void adicionaDuplo(const T& dado) {
		if (listaVazia()) {
			adicionaNoInicioDuplo(dado);
		} else {
			tail->setProximo(std::make_shared<Elemento<T>>(dado, tail, nullptr));
			tail = tail->getProximo();
			++size;
		}
	}

	/**
	 * @brief      Retira o dado no final da lista e o retorna
	 *
	 * @return     O dado retirado
	 */
	T retiraDuplo() {
		if (listaVazia())
			throw std::runtime_error("lista vazia");

		T dado = tail->getInfo();

		tail = tail->getAnterior();

		return dado;
	}

	/**
	 * @brief      Retira o dado que for igual ao dado de entrada
	 *
	 * @param[in]  dado  Dado a ser retirado
	 *
	 * @return     O dado retirado
	 */
	T retiraEspecificoDuplo(const T& dado) {
		return retiraDaPosicaoDuplo(posicaoDuplo(dado));
	}

	/**
	 * @brief      Retorna o elemento guardado na posição informada
	 *
	 * @param[in]  pos   A posição na qual o dado é desejado
	 *
	 * @return     O valor na posição pos
	 */
	T mostra(int pos) {
		return getPtr(pos)->getInfo();
	}

	/**
	 * @brief      Adiciona na lista, mantendo a ordenação dos elementos
	 *
	 * @param[in]  data  Dado a ser adicionado
	 */
	void adicionaEmOrdem(const T& data) {
		if(listaVazia())
			adicionaNoInicioDuplo(data);

		int pos = 0;

		auto e = head;

		while (pos <= size && data > e->getInfo())
			pos++;

		adicionaNaPosicaoDuplo(data, pos);
	}


	/**
	 * @brief      Mostra o tamanho da lista
	 *
	 * @return     O tamanho da lista
	 */
	int verUltimo() {
		return size;
	}

	/**
	 * @brief      Testa se a lista está vazia
	 *
	 * @return     true se estiver vazia, se não, false
	 */
	bool listaVazia() const {
		return size == 0;
	}

	/**
	 * @brief      Testa se dado1 é igual a dado2
	 *
	 * @param[in]  dado1  O primeiro dado a ser testado
	 * @param[in]  dado2  O segundo dado a ser testanto
	 *
	 * @return     true se dado1 == dado2, se não, false
	 */
	bool igual(T dado1, T dado2) {
		return dado1 == dado2;
	}

	/**
	 * @brief      Testa se dado1 é maior que dado2
	 *
	 * @param[in]  dado1  O primeiro dado a ser testado
	 * @param[in]  dado2  O segundo dado a ser testanto
	 *
	 * @return     true se dado1 > dado2, se não, false
	 */
	bool maior(T dado1, T dado2) {
		return dado1 > dado2;
	}

	/**
	 * @brief      Testa se dado1 é menor que dado2
	 *
	 * @param[in]  dado1  O primeiro dado a ser testado
	 * @param[in]  dado2  O segundo dado a ser testanto
	 *
	 * @return     true se dado1 < dado2, se não, false
	 */
	bool menor(T dado1, T dado2) {
		return dado1 < dado2;
	}

	/**
	 * @brief      Destrói a lista, removendo todos os elementos
	 */
	void destroiListaDuplo() {
		head = nullptr;
		tail = nullptr;
		size = 0;
	}

 private:
	std::shared_ptr<Elemento<T>> getPtr(int pos) {
		if (pos >= size || pos < 0)
			throw std::runtime_error("expected 0 < pos <= size");

		if (pos < size/2) {
			auto e = head;

			for (int i = 0; i < pos; ++i)
				e = e->getProximo();

			return e;

		} else {
			auto e = tail;

			for (int i = size-1; i > pos; --i)
				e = e->getAnterior();

			return e;
		}
	}
};

#endif  // LISTADUPLA_HPP
