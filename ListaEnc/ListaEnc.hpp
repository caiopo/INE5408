#ifndef LISTAENC_HPP
#define LISTAENC_HPP

#include "Elemento.hpp"
#include <stdexcept>
#include <memory>

template<typename T>
class ListaEnc {

 private:
	std::shared_ptr<Elemento<T>> head = nullptr;
	int size = 0;

 public:
	ListaEnc() = default;

	~ListaEnc() {
		destroiLista();
	}

	// inicio
	void adicionaNoInicio(const T& dado) {
		head = std::make_shared<Elemento<T>>(dado, head);;
		++size;
	}

	T retiraDoInicio() {
		if (listaVazia())
			throw std::runtime_error("lista vazia");

		T info_rmv = head->getInfo();
		head = head->getProximo();
		size--;

		return info_rmv;
	}

	void eliminaDoInicio() {
		head = head->getProximo();
		size--;
	}

	// posicao
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

		size++;
	}

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

	T* posicaoMem(const T& dado) const {
		if (listaVazia())
			throw std::runtime_error("lista vazia");

		for (auto e = head; e->getProximo() != nullptr; e = e->getProximo())
			if (e->getInfo() == dado)
				return &e->getInfo();
	}

	bool contem(const T& dado) {
		try {
			posicao(dado);
		} catch (std::runtime_error& err) {
			return false;
		}

		return true;
	}

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

	//fim
	void adiciona(const T& dado) {
		if (listaVazia())
			return adicionaNoInicio(dado);

		auto e = head;

		for (; e->getProximo(); e = e->getProximo());

		e->setProximo(std::make_shared<Elemento<T>>(dado, nullptr));

		++size;

	}

	T retira() {
		if (listaVazia())
			throw std::runtime_error("lista vazia");

		if (size == 1)
			return retiraDoInicio();

		auto e = head;

		for (; e->getProximo()->getProximo(); e = e->getProximo());

		// T data = e->getInfo();
		T data = e->getProximo()->getInfo();

		e->setProximo(nullptr);

		--size;

		return data;
	}

	// especifico
	T retiraEspecifico(const T& dado) {
		return retiraDaPosicao(posicao(dado));
	}

	void adicionaEmOrdem(const T& data) {
		if(listaVazia())
			adicionaNoInicio(data);

		int pos = 0;

		auto e = head;

		while (pos <= size && data > e->getInfo())
			pos++;

		adicionaNaPosicao(data, pos);
	}

	bool listaVazia() const {
		return size == 0;
	}

	bool igual(T dado1, T dado2) {
		return dado1 == dado2;
	}

	bool maior(T dado1, T dado2) {
		return dado1 > dado2;
	}

	bool menor(T dado1, T dado2) {
		return dado1 < dado2;
	}

	void destroiLista() {
		// auto e = head;

		// while (e) {
		// 	e = e->getProximo();
		// 	eliminaDoInicio();
		// }

		head = nullptr;
		size = 0;

	}

	// void print() {
	// 	auto e = head;

	// 	std::cout << std::endl;
	// 	std::cout << std::endl;


	// 	while (e) {

	// 		std::cout << e->getInfo() << std::endl;
	// 	e = e->getProximo();
	// 	}		std::cout << std::endl;

	// }

};

#endif  // LISTAENC_HPP