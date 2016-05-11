// Copyright 2016 Caio Pereira Oliveira

#include <memory>
#include <stdexcept>
#include "Elemento.hpp"

/**
 * @brief      Implementa uma Lista Dupla Circular, similar a uma Lista
 *             Encadeada, mas onde o último elemento aponta pro primeiro e todos
 *             os elementos também possuem um ponteiro para o anterior
 *
 * @tparam     T     Parâmetro de Template
 */
template<typename T>
class ListaDuplaCirc {
 private:
	std::shared_ptr<Elemento<T>> head;  // Ponteiro para o
										// elemento sentinela

	int size = 0;						// Tamanho da lista

 public:
	/**
	 * @brief      Construtor da lista. Inicia a lista vazia e o sentinela
	 */
	ListaDuplaCirc() {
		size = 0;
		head = std::make_shared<Elemento<T>>((T) 0, nullptr, nullptr);
		head->setProximo(head);
		head->setAnterior(head);
	}

	/**
	 * @brief      Destrutor da lista. Deleta todos os elementos para impedir
	 *             vazamento de memória
	 */
	~ListaDuplaCirc() {
		destroiListaDuplo();
	}

	/**
	 * @brief      Adiciona um dado no inicio da lista
	 *
	 * @param[in]  dado  Dado a ser adicionado
	 */
	void adicionaNoInicioDuplo(const T& dado) {
		auto novo = std::make_shared<Elemento<T>>(dado, head, head->getProximo());
		head->getProximo()->setAnterior(novo);
		head->setProximo(novo);
		++size;
	}

	/**
	 * @brief      Retira e retorna o dado armazenado no primeiro elemento após
	 *             o sentinela
	 *
	 * @return     Dado removido
	 */
	T retiraDoInicioDuplo() {
		if (listaVazia())
			throw std::runtime_error("lista vazia");
		T dado = head->getProximo()->getInfo();

		head->setProximo(head->getProximo()->getProximo());

		--size;

		return dado;
	}

	/**
	 * @brief      Deleta o elemento no head, destruindo o dado junto
	 */
	void eliminaDoInicioDuplo() {
		auto e = head->getProximo();

		e->getAnterior()->setProximo(e->getProximo());
		e->getProximo()->setAnterior(e->getAnterior());

		--size;
	}

	/**
	 * @brief      Adiciona o dado na posição
	 *
	 * @param[in]  dado  Dado a ser inserido
	 * @param[in]  pos   Posição para inserir o dado
	 */
	void adicionaNaPosicaoDuplo(const T& dado, int pos) {
		if(pos > size || pos < 0)
			throw std::runtime_error("posicao must be smaller than "
									 "ultimo+1 and greater than zero");

		if (pos == 0)
			return adicionaNoInicioDuplo(dado);

		if (pos == size)
			return adicionaDuplo(dado);

		auto e = getPtr(pos-1);

		auto novo = std::make_shared<Elemento<T>>(dado, e, e->getProximo());

		e->getProximo()->setAnterior(novo);

		e->setProximo(novo);

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

		auto e = head->getProximo();

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
		return &posicao(dado)->getInfo();
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
	T retiraDaPosicaoDuplo(int pos) {
		if (listaVazia())
			throw std::runtime_error("lista vazia");

		if (size == 1)
			return retiraDoInicioDuplo();

		if (pos == size-1)
			return retiraDuplo();

		auto e = getPtr(pos);

		T dado = e->getInfo();

		e->getAnterior()->setProximo(e->getProximo());
		e->getProximo()->setAnterior(e->getAnterior());

		--size;

		return dado;
	}

	/**
	 * @brief      Adiciona o dado no final da lista
	 *
	 * @param[in]  dado   Dado a ser adicionado
	 */
	void adicionaDuplo(const T& dado) {
		if (listaVazia())
			return adicionaNoInicioDuplo(dado);

		auto novo = std::make_shared<Elemento<T>>(dado, head->getAnterior(), head);

		head->getAnterior()->setProximo(novo);

		head->setAnterior(novo);

		++size;
	}

	/**
	 * @brief      Retira o dado no final da lista e o retorna
	 *
	 * @return     O dado retirado
	 */
	T retiraDuplo() {
		if (listaVazia())
			throw std::runtime_error("lista vazia");

		if (size == 1)
			return retiraDoInicioDuplo();

		auto e = getPtr(size-1);

		T dado = e->getInfo();

		e->getAnterior()->setProximo(e->getProximo());
		e->getProximo()->setAnterior(e->getAnterior());

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

		auto e = head->getProximo();

		while (pos < size && data > e->getInfo()) {
			pos++;
			e = e->getProximo();
		}

		adicionaNaPosicaoDuplo(data, pos);
	}

	/**
	 * @brief      Mostra o tamanho da lista
	 *
	 * @return     O tamanho da lista
	 */
	int verUltimo() {
		return size-1;
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
		while (size) {
			head->setAnterior(nullptr);
			head = head->getProximo();
			--size;
		}

		head = std::make_shared<Elemento<T>>((T) 0, nullptr, nullptr);
		head->setProximo(head);
		head->setAnterior(head);
	}

 private:
	std::shared_ptr<Elemento<T>> getPtr(int pos) {
		if (pos >= size || pos < 0)
			throw std::runtime_error("expected 0 <= pos < size");

		if (pos < size/2) {
			auto e = head->getProximo();

			for (int i = 0; i < pos; ++i)
				e = e->getProximo();

			return e;
		} else {
			auto e = head->getAnterior();
			// auto e = head->getAnterior();

			for (int i = size-1; i > pos; --i)
				e = e->getAnterior();

			return e;
		}
	}
};

