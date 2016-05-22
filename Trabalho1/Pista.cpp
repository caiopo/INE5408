#include "Pista.hpp"
#include "Exceptions.hpp"
#include <cstdlib>
#include <sstream>

Pista::Pista(Semaforo& s, Direcao d, int tam, int vel):
	semaforo(s),
	direcao(d),
	tamanho(tam),
	velocidade(vel) {}

void Pista::adiciona(Carro c) {
	if (c.getSize() > tamanho) {
		std::stringstream ss;
		ss << "pista cheia: " << direcao << " tam: " << tamanho
			<< " vel: " << velocidade << "\n";
		throw std::runtime_error(ss.str());
	}


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

void Pista::moveCarro() {
	throw std::logic_error("Pista::moveCarro not implemented");
}

int Pista::tempoParaPercorrer() {
	return tamanho / velocidade / 3.6;
}

PistaCentro::PistaCentro(Semaforo& s, Direcao d, int tam, int vel,
		Pista& sDir, Pista& sReto, Pista& sEsq):
	Pista(s, d, tam, vel),
	saidaDir(sDir),
	saidaReto(sReto),
	saidaEsq(sEsq) {}


void PistaCentro::moveCarro() {
	if (semaforo.direcaoAtual() != direcao)
		throw SemaforoNaoEstaNaDirecao();

	Direcao dir	= semaforo.decideDirecao(direcao);

	auto c = retira();

	if (dir == DirecaoFunc::getDireita(direcao)) {
			saidaDir.adiciona(c);
			throw saidaDir;

	} else if (dir == DirecaoFunc::getReto(direcao)) {
		saidaReto.adiciona(c);
		throw saidaReto;

	} else if (dir == DirecaoFunc::getEsquerda(direcao)) {
		saidaEsq.adiciona(c);
		throw saidaEsq;

	} else
		throw std::logic_error("error in PistaCentro::moveCarro");
}

Fonte::Fonte(Semaforo& s, Direcao d, int tam, int vel, int fFixa, int fVar,
	Pista& sDir, Pista& sReto, Pista& sEsq):
	Pista(s, d, tam, vel),
	frequenciaFixa(fFixa - fVar),
	frequenciaVariavel(2*fVar),
	saidaDir(sDir),
	saidaReto(sReto),
	saidaEsq(sEsq) {}

void Fonte::criaCarro() {
	Carro c;

	std::cout << "Carro entrando no sistema. Tamanho: " << c.getSize() << "\n";

	adiciona(c);
}

void Fonte::moveCarro() {
	if (semaforo.direcaoAtual() != direcao)
		throw SemaforoNaoEstaNaDirecao();

	Direcao dir	= semaforo.decideDirecao(direcao);

	auto c = retira();

	if (dir == DirecaoFunc::getDireita(direcao)) {
		saidaDir.adiciona(c);
		throw saidaDir;

	} else if (dir == DirecaoFunc::getReto(direcao)) {
		saidaReto.adiciona(c);
		throw saidaReto;

	} else if (dir == DirecaoFunc::getEsquerda(direcao)) {
		saidaEsq.adiciona(c);
		throw saidaEsq;
	} else
		throw std::logic_error("error in Fonte::moveCarro");
}

int Fonte::tempoProximoEvento(int tempo) {
	return tempo+frequenciaFixa+frequenciaVariavel*float(rand())/RAND_MAX;
}

Sumidouro::Sumidouro(Semaforo& s, Direcao d, int tam, int vel):
	Pista(s, d, tam, vel) {}