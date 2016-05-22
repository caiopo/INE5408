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

std::vector<std::shared_ptr<Evento>> Evento::run() {
	throw std::logic_error("Evento::run can not be called");
}

int Evento::getTempo() {
	return tempo;
}

EventoCriarCarro::EventoCriarCarro(int t, Fonte& f) :
	Evento(t), fonte(f) {}

EventoRemoverCarro::EventoRemoverCarro(int t, Sumidouro& s) :
	Evento(t), sumidouro(s) {}

EventoChegouNoSemaforo::EventoChegouNoSemaforo(int t, Pista& p) :
	Evento(t), pista(p) {}

EventoAbrirSemaforo::EventoAbrirSemaforo(int t, std::string m, Semaforo& s, int f) :
	Evento(t), msg(m), semaforo(s), frequencia(f) {}

std::vector<std::shared_ptr<Evento>> EventoCriarCarro::run() {
	fonte.criaCarro();

	std::vector<std::shared_ptr<Evento>> newEvents;

	int tempoProx = fonte.tempoProximoEvento(getTempo());

	newEvents.push_back(std::make_shared<EventoCriarCarro>(tempoProx, fonte));

	newEvents.push_back(std::make_shared<EventoChegouNoSemaforo>(tempoProx, fonte));

	return newEvents;
}

std::vector<std::shared_ptr<Evento>> EventoRemoverCarro::run() {
	std::cout << "Removendo carro" << "\n";

	sumidouro.retira();

	std::vector<std::shared_ptr<Evento>> newEvents;

	return newEvents;
}

std::vector<std::shared_ptr<Evento>> EventoChegouNoSemaforo::run() {
	std::cout << "Chegou no semaforo" << "\n";

	std::vector<std::shared_ptr<Evento>> newEvents;

	// try {
		pista.moveCarro();
	// }

	newEvents.push_back(std::make_shared<EventoChegouNoSemaforo>(getTempo()+5, pista));

	return newEvents;
}

std::vector<std::shared_ptr<Evento>> EventoAbrirSemaforo::run() {
	std::cout << msg << "\n";

	semaforo.proximoEstado();

	std::vector<std::shared_ptr<Evento>> newEvents;

	newEvents.push_back(std::make_shared<EventoAbrirSemaforo>(getTempo()+frequencia, msg, semaforo, frequencia));

	return newEvents;
}
