#include "Pista.hpp"
#include "Exceptions.hpp"

Pista::Pista(int tam) : size(tam) {}

void Pista::adiciona(Carro c) {
	if (c.getSize() > size)
		throw ErroPistaCheia();

	size -= c.getSize();

	fila.inclui(c);
}

Carro Pista::retira() {
	auto c = fila.retira();

	size += c.getSize();

	return c;
}

bool Pista::estaVazia() {
	return fila.filaVazia();
}
