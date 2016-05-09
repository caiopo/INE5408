#include "Pista.hpp"
#include "Exceptions.hpp"

Pista::Pista(int tam, int vel, int fFixa, int fVar):
	tamanho(tamanho), velocidade(vel),
	frenquenciaFixa(fFixa), frenquenciaVariavel(fVar) {}

void Pista::adiciona(Carrotamanho c) {
	if (c.getSize() > tamanho)
		throw ErroPistaCheia();

	tamanho -= c.getSize();

	fila.inclui(c);
}

Carro Pista::retira() {
	auto c = fila.retira();

	tamanho += c.getSize();

	return c;
}

bool Pista::estaVazia() {
	return fila.filaVazia();
}
