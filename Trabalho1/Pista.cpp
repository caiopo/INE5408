#include "Pista.hpp"
#include "Exceptions.hpp"

Pista::Pista(Direcao d, int tam, int vel):
	direcao(d),
	tamanho(tam),
	velocidade(vel) {}

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

bool Pista::moveCarro(Semaforo&) {
	throw std::logic_error("Pista::moveCarro not implemented");
}

PistaCentro::PistaCentro(Direcao d, int tam, int vel,
		Pista& sDir, Pista& sReto, Pista& sEsq):
	Pista(d, tam, vel),
	saidaDir(sDir),
	saidaReto(sReto),
	saidaEsq(sEsq) {}


bool PistaCentro::moveCarro(Semaforo& semaforo) {
	if (semaforo.direcaoAtual() != direcao)
		return false;

	Direcao dir	= semaforo.decideDirecao(direcao);

	auto c = retira();

	if (dir == DirecaoFunc::getDireita(direcao))
		saidaDir.adiciona(c);
	else if (dir == DirecaoFunc::getReto(direcao))
		saidaReto.adiciona(c);
	else if (dir == DirecaoFunc::getEsquerda(direcao))
		saidaEsq.adiciona(c);
	else
		throw std::logic_error("error in PistaCentro::moveCarro");

	return true;
}

Fonte::Fonte(Direcao d, int tam, int vel, int fFixa, int fVar,
	Pista& sDir, Pista& sReto, Pista& sEsq):
	Pista(d, tam, vel),
	frequenciaFixa(fFixa - fVar),
	frequenciaVariavel(2*fVar),
	saidaDir(sDir),
	saidaReto(sReto),
	saidaEsq(sEsq) {}

void Fonte::criaCarro() {
	adiciona(Carro());
}

bool Fonte::moveCarro(Semaforo& semaforo) {
	if (semaforo.direcaoAtual() != direcao)
		return false;

	Direcao dir	= semaforo.decideDirecao(direcao);

	auto c = retira();

	if (dir == DirecaoFunc::getDireita(direcao))
		saidaDir.adiciona(c);
	else if (dir == DirecaoFunc::getReto(direcao))
		saidaReto.adiciona(c);
	else if (dir == DirecaoFunc::getEsquerda(direcao))
		saidaEsq.adiciona(c);
	else
		throw std::logic_error("error in Fonte::moveCarro");

	return true;
}

Sumidouro::Sumidouro(Direcao d, int tam, int vel):
	Pista(d, tam, vel) {}