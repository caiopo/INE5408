#ifndef LISTAORDENADA_HPP
#define LISTAORDENADA_HPP

#include "Evento.hpp"
#include "ListaEnc.hpp"

template<typename T>
class ListaOrdenada {
private:
	ListaEnc<T> lista;
public:
	ListaOrdenada() = default;
	void adiciona(T e);
	T retira();
	bool estaVazia();
	int getSize();
};

template<typename T>
void ListaOrdenada<T>::adiciona(T e) {
	lista.adicionaEmOrdem(e);
}

template<typename T>
T ListaOrdenada<T>::retira() {
	return lista.retiraDoInicio();
}

template<typename T>
bool ListaOrdenada<T>::estaVazia() {
	return lista.listaVazia();
}

template<typename T>
int ListaOrdenada<T>::getSize() {
	return lista.getSize();
}

#endif  // LISTAORDENADA_HPP
