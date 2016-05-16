#ifndef EVENTO_HPP
#define EVENTO_HPP

#include "Carro.hpp"
#include "Semaforo.hpp"
#include "Pista.hpp"
#include <memory>

class Evento {
private:
	int tempo = 0;

public:
	explicit Evento(int t) : tempo(t) {}
	virtual~Evento() {}

	int getTempo();

	bool operator >(const Evento& e) const;
	bool operator <(const Evento& e) const;
	bool operator ==(const Evento& e) const;
	bool operator >=(const Evento& e) const;
	bool operator <=(const Evento& e) const;

	bool operator >(int i) const;
	bool operator <(int i) const;
	bool operator ==(int i) const;
	bool operator >=(int i) const;
	bool operator <=(int i) const;

};

class EventoCriarCarro : public Evento {
private:
	Pista& pista;

public:
	EventoCriarCarro(int t, Pista& p);
};

class EventoRemoverCarro : public Evento {
private:
	Pista& pista;

public:
	EventoRemoverCarro(int t, Pista& p);
};

class EventoChegouNoSemaforo : public Evento {
private:
	Semaforo& semaforo;
	Pista& pista;
public:
	EventoChegouNoSemaforo(int t, Semaforo& s, Pista& p);
};

class EventoAbrirSemaforo : public Evento {
private:
	Semaforo& semaforo;
public:
	EventoAbrirSemaforo(int t, Semaforo& s);
};


#endif  // EVENTO_HPP