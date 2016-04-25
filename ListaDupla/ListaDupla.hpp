#ifndef LISTADUPLA_HPP
#define LISTADUPLA_HPP

#include "Elemento.hpp"
#include <memory>
#include <stdexcept>
#include <iostream>

template<typename T>
class ListaDupla {
 private:
 	std::shared_ptr<Elemento<T>> head;
 	std::shared_ptr<Elemento<T>> tail;
 	int size = 0;

	// std::shared_ptr<Elemento<T>> getPtr(int pos);

 public:
	ListaDupla() = default;

	~ListaDupla() {
		destroiListaDuplo();
	}

	void adicionaNoInicioDuplo(const T& dado) {
		head = std::make_shared<Elemento<T>>(dado, nullptr, head);

		if (listaVazia())
			tail = head;

		++size;
	}

	T retiraDoInicioDuplo() {
		if (listaVazia())
			throw std::runtime_error("lista vazia");

		T dado = head->getInfo();

		head = head->getProximo();

		--size;

		return dado;
	}

	void eliminaDoInicioDuplo() {
		if (listaVazia())
			throw std::runtime_error("lista vazia");

		head = head->getProximo();
		--size;
	}

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

	T* posicaoMemDuplo(const T& dado) const {
		if (listaVazia())
			throw std::runtime_error("lista vazia");

		for (auto e = head; e->getProximo() != nullptr; e = e->getProximo())
			if (e->getInfo() == dado)
				return &e->getInfo();
	}

	bool contemDuplo(const T& dado) {
		try {
			posicaoDuplo(dado);
		} catch (std::runtime_error& e) {
			return false;
		}

		return true;
	}

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

	void adicionaDuplo(const T& dado) {
		if (listaVazia())
			adicionaNoInicioDuplo(dado);
		else {
			tail->setProximo(std::make_shared<Elemento<T>>(dado, tail, nullptr));
			tail = tail->getProximo();
			++size;
		}
	}

	T retiraDuplo() {
		if (listaVazia())
			throw std::runtime_error("lista vazia");

		T dado = tail->getInfo();

		tail = tail->getAnterior();

		return dado;
	}

	T retiraEspecificoDuplo(const T& dado) {
		return retiraDaPosicaoDuplo(posicaoDuplo(dado));
	}

	T mostra(int pos) {
		return getPtr(pos)->getInfo();
	}

	void adicionaEmOrdem(const T& data) {
		if(listaVazia())
			adicionaNoInicioDuplo(data);

		int pos = 0;

		auto e = head;

		while (pos <= size && data > e->getInfo())
			pos++;

		adicionaNaPosicaoDuplo(data, pos);
	}

	int verUltimo() {
		return size;
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

	void destroiListaDuplo() {
		head = nullptr;
		tail = nullptr;
		size = 0;
	}

	void print() {
		for (auto e = head; e; e = e->getProximo()) {
			std::cout << e->getInfo() << " ";
		}

		std::cout << std::endl;
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