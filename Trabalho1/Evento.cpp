#include "Evento.hpp"
#include <stdexcept>

bool Evento::operator>(const Evento& e) const {
	return tempo > e.tempo;
}

bool Evento::operator<(const Evento& e) const {
	return tempo < e.tempo;
}

bool Evento::operator==(const Evento& e) const {
	return tempo == e.tempo;
}

bool Evento::operator!=(const Evento& e) const {
	return tempo != e.tempo;
}

bool Evento::operator>=(const Evento& e) const {
	return tempo >= e.tempo;
}

bool Evento::operator<=(const Evento& e) const {
	return tempo <= e.tempo;
}

bool Evento::operator>(int i) const {
	return tempo > i;
}

bool Evento::operator<(int i) const {
	return tempo < i;
}

bool Evento::operator==(int i) const {
	return tempo == i;
}

bool Evento::operator!=(int i) const {
	return tempo != i;
}

bool Evento::operator>=(int i) const {
	return tempo >= i;
}

bool Evento::operator<=(int i) const {
	return tempo <= i;
}

Evento::Evento(int t) : tempo(t) {}

std::vector<Evento> Evento::run() {
	throw std::logic_error("");
}

int Evento::getTempo() {
	return tempo;
}

EventoCriarCarro::EventoCriarCarro(int t, Fonte& f) :
	Evento(t), fonte(f) {}

EventoRemoverCarro::EventoRemoverCarro(int t, Sumidouro& s) :
	Evento(t), sumidouro(s) {}

EventoChegouNoSemaforo::EventoChegouNoSemaforo(int t, Semaforo& s, Pista& p) :
	Evento(t), semaforo(s), pista(p) {}

EventoAbrirSemaforo::EventoAbrirSemaforo(int t, Semaforo& s) :
	Evento(t), semaforo(s) {}

std::vector<Evento> EventoCriarCarro::run() {
	fonte.criaCarro();

	std::vector<Evento> newEvents;

}

std::vector<Evento> EventoRemoverCarro::run() {
	sumidouro.retira();

	std::vector<Evento> newEvents;

}

std::vector<Evento> EventoChegouNoSemaforo::run() {
	pista.moveCarro(semaforo);

	std::vector<Evento> newEvents;

}

std::vector<Evento> EventoAbrirSemaforo::run() {
	semaforo.proximoEstado();

	std::vector<Evento> newEvents;
}
