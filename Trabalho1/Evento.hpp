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
	~Evento() {}

	int getTempo();
	virtual void calcula();

	bool operator >(const Evento& e) const;
	bool operator <(const Evento& e) const;
	bool operator ==(const Evento& e) const;
	bool operator >=(const Evento& e) const;
	bool operator <=(const Evento& e) const;

};

class EventoCriarCarro : public Evento {
private:
	std::shared_ptr<Pista> pista;

public:
	EventoCriarCarro(int t, Pista& p);
	~EventoCriarCarro() {}
};

class EventoRemoverCarro : public Evento {
private:
	std::shared_ptr<Carro> carro;
	std::shared_ptr<Pista> pista;

public:
	EventoRemoverCarro(int t, Carro& c, Pista& p);
	~EventoRemoverCarro() {}
};

class EventoChegouNoSemaforo : public Evento {
private:
	std::shared_ptr<Carro> carro;
	std::shared_ptr<Semaforo> semaforo;
	std::shared_ptr<Pista> pista;
public:
	EventoChegouNoSemaforo(int t, Carro& c, Semaforo& s);
	~EventoChegouNoSemaforo() {}
};

class EventoAbrirSemaforo : public Evento {
private:
	std::shared_ptr<Semaforo> semaforo;
public:
	EventoAbrirSemaforo(int t, Semaforo& s);
	~EventoAbrirSemaforo() {}
};


#endif  // EVENTO_HPP