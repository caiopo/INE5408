#ifndef LISTAORDENADA_HPP
#define LISTAORDENADA_HPP

#include "ListaEnc.hpp"
#include "Evento.hpp"

class ListaOrdenada {
private:
	ListaEnc<Evento> lista;
public:
	ListaOrdenada() = default;
	void adiciona(Evento e);
	Evento retira();
	bool estaVazia();
};

#endif  // LISTAORDENADA_HPP
