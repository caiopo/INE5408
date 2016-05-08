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

EventoCriarCarro::EventoCriarCarro(int t, Pista& p) :
	Evento(t), pista(std::make_shared<Pista>(p)) {}

EventoRemoverCarro::EventoRemoverCarro(int t, Carro& c, Pista& p) :
	Evento(t), carro(std::make_shared<Carro>(c)), pista(std::make_shared<Pista>(p)) {}

EventoChegouNoSemaforo::EventoChegouNoSemaforo(int t, Carro& c, Semaforo& s) :
	Evento(t), carro(std::make_shared<Carro>(c)), semaforo(std::make_shared<Semaforo>(s)) {}

EventoAbrirSemaforo::EventoAbrirSemaforo(int t, Semaforo& s) :
	Evento(t), semaforo(std::make_shared<Semaforo>(s)) {}
