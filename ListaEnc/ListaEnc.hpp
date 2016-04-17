#ifndef LISTAENC_HPP
#define LISTAENC_HPP

#include "Elemento.hpp"
#include <cstdio>
#include <stdexcept>
#include <iostream>


template<typename T>
class ListaEnc {

 private:
	Elemento<T>* head = nullptr;
	int size = 0;

 public:
	ListaEnc() = default;

	~ListaEnc() {
		destroiLista();
	}

	// inicio
	void adicionaNoInicio(const T& dado) {
		head = new Elemento<T>(dado, head);;
		++size;
	}

	T retiraDoInicio() {
		if (listaVazia())
			throw std::runtime_error("lista vazia");

		Elemento<T>* removido = head;
		head = head->getProximo();
		T info_rmv = removido->getInfo();
		delete removido;

		size--;

		return info_rmv;
	}

	void eliminaDoInicio() {
		Elemento<T>* removido = head;
		head = head->getProximo();
		delete removido;

		size--;
	}

	// posicao
	void adicionaNaPosicao(const T& dado, int pos) {
		if(pos > size+1 || pos < 0)
			throw std::runtime_error("posicao must be smaller than "
									"ultimo+1 and greater than zero");

		if (pos == 0) {
			return adicionaNoInicio(dado);

		if (pos == size+1)
			return adiciona(dado);

		Elemento<T>* e = head;

		for (int i = 0; i < pos-2; ++i) {
			e = e->getProximo();
		}

		e->setProximo(new Elemento<T>(dado, e->getProximo()));

		size++;
	}

	int posicao(const T& dado) const {
		if (listaVazia())
			throw std::runtime_error("lista vazia");

		Elemento<T>* e = head;

		int i = 0;

		do {
			if (dado == e->getInfo())
				return i;

			++i;
			e = e->getProximo();
		} while(e);

		throw std::runtime_error("dado não encontrado");
	}

	T* posicaoMem(const T& dado) const {
		if (listaVazia())
			throw std::runtime_error("lista vazia");

		for (Elemento<T>* e = head; e->getProximo() != nullptr; e = e->getProximo())
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

		Elemento<T>* e = head;

		for (int i = 0; i < pos-2; ++i)
			e = e->getProximo();

		Elemento<T>* removido = e->getProximo();

		e->setProximo(removido->getProximo());

		T dado = e->getInfo();

		delete removido;

		size--;

		return dado;

	}

	//fim
	void adiciona(const T& dado) {
		if (listaVazia())
			return adicionaNoInicio(dado);

		Elemento<T>* e = head;

		// while(e && e->getProximo())
		// 	e = e->getProximo();

		for (; e->getProximo(); e = e->getProximo());

		e->setProximo(new Elemento<T>(dado, nullptr));

	}

	T retira() {
		if (listaVazia())
			throw std::runtime_error("lista vazia");

		Elemento<T>* e = head;

		// while(e && e->getProximo())
		// 	e = e->getProximo();

		for (; e->getProximo(); e = e->getProximo());

		T data = e->getInfo();

		delete e->getProximo();

		e->setProximo(nullptr);

		size--;

		return data;
	}

	// especifico
	T retiraEspecifico(const T& dado) {
		int pos = posicao(dado);
		return retiraDaPosicao(pos);
	}

	void adicionaEmOrdem(const T& data) {
		if(listaVazia())
			adicionaNoInicio(data);

		int pos = 0;
		Elemento<T>* e = head;

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
		Elemento<T>* e = head;

		while (e) {
			e = e->getProximo();
			eliminaDoInicio();
		}

	}

	void print() {
		Elemento<T>* e = head;

		std::cout << std::endl;
		std::cout << std::endl;

		while (e) {
			std::cout << e->getInfo() << std::endl;
			e = e->getProximo();
		}

		std::cout << std::endl;
		std::cout << std::endl;

	}

};

#endif  // LISTAENC_HPP