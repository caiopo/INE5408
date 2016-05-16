#include "Pista.hpp"
#include "Exceptions.hpp"

Pista::Pista(int tam, int vel, int fFixa, int fVar,
		Pista& sDir, Pista& sReto, Pista& sEsq):
	tamanho(tam),
	velocidade(vel),
	frequenciaFixa(fFixa),
	frequenciaVariavel(fVar),
	saidaDir(sDir),
	saidaReto(sReto),
	saidaEsq(sEsq) {}

void Pista::adiciona(Carro c) {
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
