#include "ListaOrdenada.hpp"

void ListaOrdenada::adiciona(Evento e) {
	lista.adicionaEmOrdem(e);
}

Evento ListaOrdenada::retira() {
	return lista.retiraDoInicio();
}

bool ListaOrdenada::estaVazia() {
	return lista.listaVazia();
}
