#ifndef EVENTO_HPP
#define EVENTO_HPP

#include "Carro.hpp"
#include "Semaforo.hpp"
#include "Pista.hpp"
#include <vector>

class Evento {
private:
	int tempo = 0;

public:
	explicit Evento(int t);
	virtual ~Evento() {}
	virtual std::vector<Evento> run();
	int getTempo();

	bool operator >(const Evento& e) const;
	bool operator <(const Evento& e) const;
	bool operator ==(const Evento& e) const;
	bool operator !=(const Evento& e) const;
	bool operator >=(const Evento& e) const;
	bool operator <=(const Evento& e) const;

	bool operator >(int i) const;
	bool operator <(int i) const;
	bool operator ==(int i) const;
	bool operator !=(int i) const;
	bool operator >=(int i) const;
	bool operator <=(int i) const;
};

class EventoCriarCarro : public Evento {
private:
	Fonte& fonte;
public:
	EventoCriarCarro(int t, Fonte& f);
	std::vector<Evento> run();
};

class EventoRemoverCarro : public Evento {
private:
	Sumidouro& sumidouro;
public:
	EventoRemoverCarro(int t, Sumidouro& s);
	std::vector<Evento> run();
};

class EventoChegouNoSemaforo : public Evento {
private:
	Semaforo& semaforo;
	Pista& pista;
public:
	EventoChegouNoSemaforo(int t, Semaforo& s, Pista& p);
	std::vector<Evento> run();
};

class EventoAbrirSemaforo : public Evento {
private:
	Semaforo& semaforo;
	int frequencia;
public:
	EventoAbrirSemaforo(int t, Semaforo& s, int f);
	std::vector<Evento> run();
};

#endif  // EVENTO_HPP
