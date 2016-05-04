#include <sstream>

#define SSTR( x ) static_cast< std::ostringstream & >( \
        ( std::ostringstream() << std::dec << x ) ).str()


#include <memory>
#include <stdexcept>
#include "Elemento.hpp"

template<typename T>
class ListaCirc {
 private:
 	std::shared_ptr<Elemento<T>> head;
 	int size = 0;
 public:
	ListaCirc() {
		head = std::make_shared<Elemento<T>>((T) 0, nullptr);
		head->setProximo(head);
	}

	~ListaCirc() {
		destroiLista();
	}

	void adicionaNoInicio(const T& dado) {
		head->setProximo(std::make_shared<Elemento<T>>(dado, head->getProximo()));
		++size;
	}

	T retiraDoInicio() {
		if (listaVazia())
			throw std::runtime_error("lista vazia");
		T dado = head->getProximo()->getInfo();

		head->setProximo(head->getProximo()->getProximo());

		--size;

		return dado;
	}

	void eliminaDoInicio() {
		head->setProximo(head->getProximo());
		--size;
	}

	void adicionaNaPosicao(const T& dado, int pos) {
		if(pos > size || pos < 0)
			throw std::runtime_error("posicao must be smaller than "
									 "ultimo+1 and greater than zero");

		if (pos == 0)
			return adicionaNoInicio(dado);

		if (pos == size)
			return adiciona(dado);

		auto e = head;

		for (int i = 0; i < pos-1; ++i)
			e = e->getProximo();


		e->setProximo(std::make_shared<Elemento<T>>(dado, e->getProximo()));

		++size;
	}

	int posicao(const T& dado) const {
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


	T* posicaoMem(const T& dado) const {
		return &posicao(dado)->getInfo();
	}

	bool contem(const T& dado) {
		if (listaVazia())
			throw std::runtime_error("lista vazia");

		try {
			posicao(dado);
		} catch (std::runtime_error& err) {
			return false;
		}

		return true;
	}

	T retiraDaPosicao(int pos) {
		if (listaVazia())
			throw std::runtime_error("lista vazia");

		if (size == 1)
			return retiraDoInicio();

		if (pos == size-1)
			return retira();

		auto e = getPtr(pos-1);

		T dado = e->getProximo()->getInfo();

		e->setProximo(e->getProximo()->getProximo());

		--size;

		return dado;
	}

	void adiciona(const T& dado) {
		if (listaVazia())
			return adicionaNoInicio(dado);

		auto e = getPtr(size-1);

		e->setProximo(std::make_shared<Elemento<T>>(dado, head));

		++size;
	}

	T retira() {
		if (listaVazia())
			throw std::runtime_error("lista vazia");

		if (size == 1)
			return retiraDoInicio();

		auto e = getPtr(size-2);

		T dado = e->getProximo()->getInfo();

		e->setProximo(nullptr);

		return dado;
	}

	T retiraEspecifico(const T& dado) {
		return retiraDaPosicao(posicao(dado));
	}

	T mostra(int pos) {
		return getPtr(pos)->getInfo();
	}

	void adicionaEmOrdem(const T& data) {
		if(listaVazia())
			adicionaNoInicio(data);

		int pos = 0;

		auto e = head->getProximo();

		while (pos < size && data > e->getInfo()) {
			pos++;
			e = e->getProximo();
		}

		adicionaNaPosicao(data, pos);
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

	void destroiLista() {
		head = std::make_shared<Elemento<T>>((T) 0, nullptr);
		head->setProximo(head);
		size = 0;
	}

 private:
 	std::shared_ptr<Elemento<T>> getPtr(int pos) {
 		if (pos >= size || pos < 0)
 			throw std::runtime_error("pos must be 0 <= pos < size: "+SSTR(pos));

 		auto e = head->getProximo();

 		for (int i = 0; i < pos; ++i)
 			e = e->getProximo();

 		return e;
 	}

};
