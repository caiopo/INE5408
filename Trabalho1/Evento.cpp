#include "Evento.hpp"

// Evento::Evento(int t) : tempo(t) {}

int Evento::getTempo() {
	return tempo;
}

bool Evento::operator >(const Evento& e) const {
	return tempo > e.tempo;
}

bool Evento::operator <(const Evento& e) const {
	return tempo < e.tempo;
}

bool Evento::operator ==(const Evento& e) const {
	return tempo == e.tempo;
}

bool Evento::operator >=(const Evento& e) const {
	return tempo >= e.tempo;
}

bool Evento::operator <=(const Evento& e) const {
	return tempo <= e.tempo;
}

bool Evento::operator >(int i) const {
	return tempo > i;
}

bool Evento::operator <(int i) const {
	return tempo < i;
}

bool Evento::operator ==(int i) const {
	return tempo == i;
}

bool Evento::operator >=(int i) const {
	return tempo >= i;
}

bool Evento::operator <=(int i) const {
	return tempo <= i;
}

EventoCriarCarro::EventoCriarCarro(int t, Pista& p) :
	Evento(t), pista(p) {}

EventoRemoverCarro::EventoRemoverCarro(int t, Pista& p) :
	Evento(t), pista(p) {}

EventoChegouNoSemaforo::EventoChegouNoSemaforo(int t, Semaforo& s, Pista& p) :
	Evento(t), semaforo(s), pista(p) {}

EventoAbrirSemaforo::EventoAbrirSemaforo(int t, Semaforo& s) :
	Evento(t), semaforo(s) {}
