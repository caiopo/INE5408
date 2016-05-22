#ifndef EVENTO_HPP
#define EVENTO_HPP

#include "Carro.hpp"
#include "Semaforo.hpp"
#include "Pista.hpp"
#include <vector>
#include <memory>

class Evento {
private:
	int tempo = 0;

public:
	explicit Evento(int t);
	virtual ~Evento() {}
	virtual std::vector<std::shared_ptr<Evento>> run();
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
	std::vector<std::shared_ptr<Evento>> run();
};

class EventoRemoverCarro : public Evento {
private:
	Sumidouro& sumidouro;
public:
	EventoRemoverCarro(int t, Sumidouro& s);
	std::vector<std::shared_ptr<Evento>> run();
};

class EventoChegouNoSemaforo : public Evento {
private:
	Pista& pista;
public:
	EventoChegouNoSemaforo(int t, Pista& p);
	std::vector<std::shared_ptr<Evento>> run();
};

class EventoAbrirSemaforo : public Evento {
private:
	std::string msg;
	Semaforo& semaforo;
	int frequencia;
public:
	EventoAbrirSemaforo(int t, std::string msg, Semaforo& s, int f);
	std::vector<std::shared_ptr<Evento>> run();
};

#endif  // EVENTO_HPP
