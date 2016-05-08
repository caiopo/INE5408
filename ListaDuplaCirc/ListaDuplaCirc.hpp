#include <memory>
#include <stdexcept>
#include "Elemento.hpp"

template<typename T>
class ListaDuplaCirc {
 private:
 	std::shared_ptr<Elemento<T>> head;
 	int size = 0;

 public:
	ListaDuplaCirc() {
		head = std::make_shared<Elemento<T>>((T) 0, nullptr, nullptr);
		head->setProximo(head);
		head->setAnterior(head);
	}

	~ListaDuplaCirc() {
		destroiListaDuplo();
	}

	void adicionaNoInicioDuplo(const T& dado) {

	}

	T retiraDoInicioDuplo() {

	}

	void eliminaDoInicioDuplo() {
		head->setProximo(head->getProximo());
		--size;
	}

	void adicionaNaPosicaoDuplo(const T& dado, int pos) {

	}

	int posicaoDuplo(const T& dado) const {

	}

	T* posicaoMemDuplo(const T& dado) const {

	}

	bool contemDuplo(const T& dado) {

	}

	T retiraDaPosicaoDuplo(int pos) {

	}

	void adicionaDuplo(const T& dado) {

	}

	T retiraDuplo() {

	}

	T retiraEspecificoDuplo(const T& dado) {

	}

	T mostra(int pos) {

	}

	void adicionaEmOrdem(const T& data) {

	}

	int verUltimo() {

	}

	bool listaVazia() const {

	}

	bool igual(T dado1, T dado2) {

	}

	bool maior(T dado1, T dado2) {

	}

	bool menor(T dado1, T dado2) {

	}

	void destroiListaDuplo() {

		while (head) {
			head->setAnterior(nullptr);
			head = head->getProximo();
		}

		head = std::make_shared<Elemento<T>>((T) 0, nullptr, nullptr);
		head->setProximo(head);
		head->setAnterior(head);

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

