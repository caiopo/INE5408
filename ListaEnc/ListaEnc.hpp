// Copyright 2016 Caio Pereira Oliveira

#ifndef LISTAENC_HPP
#define LISTAENC_HPP

#include <stdexcept>
#include <memory>
#include "Elemento.hpp"

/**
 * @brief      Implementa uma Lista Encadeada. Uma Lista Encadeada é uma
 *             estrutura de dados linear e dinâmica. Ela é composta por células
 *             que apontam para o próximo elemento da lista. Para "ter" uma
 *             lista ligada/encadeada, basta guardar seu primeiro elemento, e
 *             seu último elemento aponta para uma célula nula. O esquema a
 *             seguir representa uma lista ligada/encadeada com 5 elementos:
 *
 *             Célula 1 ----> Célula 2 ---> Célula 3 ---> Célula 4 ---> Célula 5
 *             ---> (Nulo)
 *
 * @tparam     T     Parâmetro de Template
 */
template<typename T>
class ListaEnc {
 private:
	std::shared_ptr<Elemento<T>> head;  // Ponteiro para o
										// primeiro elemento da Lista
	int size = 0;  // Tamanho da Lista

 public:
	/**
	 * @brief      Construtor da lista. Inicia a lista vazia
	 */
	ListaEnc() = default;

	/**
	 * @brief      Destrutor da lista. Deleta todos os elementos para impedir vazamento de memória
	 */
	~ListaEnc() {
		destroiLista();
	}

	// inicio


	/**
	 * @brief      Adiciona um dado no inicio da lista, tornando-o o novo head
	 *
	 * @param[in]  dado  Dado a ser adicionado
	 */
	void adicionaNoInicio(const T& dado) {
		head = std::make_shared<Elemento<T>>(dado, head);;
		++size;
	}

	/**
	 * @brief      Retira o dado armazenado no head e o retorna o novo head passa a ser head->getProximo()
	 *
	 * @return     Dado removido
	 */
	T retiraDoInicio() {
		if (listaVazia())
			throw std::runtime_error("lista vazia");

		T info_rmv = head->getInfo();
		head = head->getProximo();
		--size;

		return info_rmv;
	}

	/**
	 * @brief      Deleta o elemento no head, destruindo o dado junto
	 */
	void eliminaDoInicio() {
		head = head->getProximo();
		--size;
	}

	// posicao


	/**
	 * @brief      Adiciona o dado na posição
	 *
	 * @param[in]  dado  Dado a ser inserido
	 * @param[in]  pos   Posição para inserir o dado
	 */
	void adicionaNaPosicao(const T& dado, int pos) {
		if(pos > size || pos < 0)
			throw std::runtime_error("posicao must be smaller than "
									"ultimo+1 and greater than zero");

		if (pos == 0)
			return adicionaNoInicio(dado);

		if (pos == size+1)
			return adiciona(dado);

		auto e = head;

		for (int i = 0; i < pos-1; ++i)
			e = e->getProximo();


		e->setProximo(std::make_shared<Elemento<T>>(dado, e->getProximo()));

		++size;
	}

	/**
	 * @brief      Retorna a menor posição na qual o dado esteja
	 *
	 * @param[in]  dado  Dado a ser procurado
	 *
	 * @return     Menor índice do dado na lista
	 */
	int posicao(const T& dado) const {
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
	T* posicaoMem(const T& dado) const {
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
	bool contem(const T& dado) {
		try {
			posicao(dado);
		} catch (std::runtime_error& err) {
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
	T retiraDaPosicao(int pos) {
		if(pos > size || pos < 0)
			throw std::runtime_error("posicao must be smaller than "
									"ultimo+1 and greater than zero");

		if (listaVazia())
			throw std::runtime_error("lista vazia");


		if (pos == 0)
			return retiraDoInicio();

		if (pos == size)
			return retira();

		auto e = head;

		for (int i = 0; i < pos-1; ++i)
			e = e->getProximo();

		T dado = e->getProximo()->getInfo();

		e->setProximo(e->getProximo()->getProximo());

		--size;

		return dado;
	}

	// fim

	/**
	 * @brief      Adiciona o dado no final da lista
	 *
	 * @param[in]  dado   Dado a ser adicionado
	 */
	void adiciona(const T& dado) {
		if (listaVazia())
			return adicionaNoInicio(dado);

		auto e = head;

		for (; e->getProximo(); e = e->getProximo()) {}

		e->setProximo(std::make_shared<Elemento<T>>(dado, nullptr));

		++size;
	}

	/**
	 * @brief      Retira o dado no final da lista e o retorna
	 *
	 * @return     O dado retirado
	 */
	T retira() {
		if (listaVazia())
			throw std::runtime_error("lista vazia");

		if (size == 1)
			return retiraDoInicio();

		auto e = head;

		for (; e->getProximo()->getProximo(); e = e->getProximo()) {}

		// T data = e->getInfo();
		T data = e->getProximo()->getInfo();

		e->setProximo(nullptr);

		--size;

		return data;
	}

	// especifico

	/**
	 * @brief      Retira o dado que for igual ao dado de entrada
	 *
	 * @param[in]  dado  Dado a ser retirado
	 *
	 * @return     O dado retirado
	 */
	T retiraEspecifico(const T& dado) {
		return retiraDaPosicao(posicao(dado));
	}

	/**
	 * @brief      Adiciona na lista, mantendo a ordenação dos elementos
	 *
	 * @param[in]  data  Dado a ser adicionado
	 */
	void adicionaEmOrdem(const T& data) {
		if(listaVazia())
			adicionaNoInicio(data);

		int pos = 0;

		auto e = head;

		while (pos <= size && data > e->getInfo())
			pos++;

		adicionaNaPosicao(data, pos);
	}

	/**
	 * @brief      Testa se a lista está vazia
	 *
	 * @tparam     T     Parâmetro de Template
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
	 * @tparam     T      Parâmetro de Template
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
	 * @tparam     T      Parâmetro de Template
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
	 * @tparam     T      Parâmetro de Template
	 *
	 * @return     true se dado1 < dado2, se não, false
	 */
	bool menor(T dado1, T dado2) {
		return dado1 < dado2;
	}

	/**
	 * @brief      Destrói a Lista, removendo todos os elementos
	 *
	 * @tparam     T     Parâmetro de Template
	 */
	void destroiLista() {
		head = nullptr;
		size = 0;
	}
};

#endif  // LISTAENC_HPP
