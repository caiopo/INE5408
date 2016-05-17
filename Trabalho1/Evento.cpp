#include "Evento.hpp"
#include <stdexcept>
#include <iostream>

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
	throw std::logic_error("Evento::run can not be called");
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

EventoAbrirSemaforo::EventoAbrirSemaforo(int t, Semaforo& s, int f) :
	Evento(t), semaforo(s), frequencia(f) {}

std::vector<Evento> EventoCriarCarro::run() {
	std::cout << "Criando carro" << "\n";

	fonte.criaCarro();

	std::vector<Evento> newEvents;

	EventoCriarCarro e(fonte.tempoProximoEvento(getTempo()), fonte);

	newEvents.push_back(e);

	return newEvents;
}

std::vector<Evento> EventoRemoverCarro::run() {
	std::cout << "Removendo carro" << "\n";

	sumidouro.retira();

	std::vector<Evento> newEvents;

	return newEvents;
}

std::vector<Evento> EventoChegouNoSemaforo::run() {
	std::cout << "Chegou no semaforo" << "\n";

	std::vector<Evento> newEvents;

	if (pista.moveCarro(semaforo)) {
		return newEvents;
	} else {
		newEvents.push_back(EventoChegouNoSemaforo(getTempo()+5, semaforo, pista));
		return newEvents;
	}

}

std::vector<Evento> EventoAbrirSemaforo::run() {
	std::cout << "Proximo estado do semaforo" << "\n";

	semaforo.proximoEstado();

	std::vector<Evento> newEvents;

	newEvents.push_back(EventoAbrirSemaforo(getTempo()+frequencia, semaforo, frequencia));

	return newEvents;
}
