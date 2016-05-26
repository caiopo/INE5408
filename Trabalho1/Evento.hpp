#ifndef EVENTO_HPP
#define EVENTO_HPP

#include "Carro.hpp"
#include "Semaforo.hpp"
#include "Pista.hpp"
#include <vector>
#include <memory>
#include <iostream>

/**
 * @brief      Classe base que representa um evento
 */
class Evento {
private:
	int tempo = 0;  // Tempo que o evento será executado

public:
	explicit Evento(int t);								 // Construtor de Evento
	virtual ~Evento() {}
	virtual std::vector<std::shared_ptr<Evento>> run();  // Executa o evento,
	                                                     // retornando os eventos que
	                                                     // deverão ser adicionados a
	                                                     // lista ordenada de eventos

	int getTempo() const;  								 // Retorna o tempo do evento

	virtual void print();                                // Imprime o evento em stdout

	// Operadores sobrecarregados
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

/**
 * @brief      Classe que representa um evento para criar carro em uma fonte
 */
class EventoCriarCarro : public Evento {
private:
	Fonte& fonte;
public:
	EventoCriarCarro(int t, Fonte& f);  // Construtor de EventoCriarCarro
	std::vector<std::shared_ptr<Evento>> run();
	void print();  // Imprime o evento em stdout
};

/**
 * @brief      Classe que representa um evento para remover um carro de um sumidouro
 */
class EventoRemoverCarro : public Evento {
private:
	Sumidouro& sumidouro;
public:
	EventoRemoverCarro(int t, Sumidouro& s);  // Construtor de EventoRemoverCarro
	std::vector<std::shared_ptr<Evento>> run();  // Executa o evento,
                                                 // retornando os eventos que
                                                 // deverão ser adicionados a
                                                 // lista ordenada de eventos
	void print();  // Imprime o evento em stdout
};

/**
 * @brief      Classe que representa um evento para trocar um carro de pista
 */
class EventoChegouNoSemaforo : public Evento {
private:
	Pista& pista;
public:
	EventoChegouNoSemaforo(int t, Pista& p);  // Construtor de EventoChegouNoSemaforo
	std::vector<std::shared_ptr<Evento>> run();  // Executa o evento,
                                                 // retornando os eventos que
                                                 // deverão ser adicionados a
                                                 // lista ordenada de eventos
	void print();  // Imprime o evento em stdout
};

/**
 * @brief      Classe que representa um evento para trocar o semáforo para o próximo estado
 */
class EventoAbrirSemaforo : public Evento {
private:
	std::string msg;
	Semaforo& semaforo;
	int frequencia;
public:
	EventoAbrirSemaforo(int t, std::string msg, Semaforo& s, int f);  // Construtor de EventoAbrirSemaforo
	std::vector<std::shared_ptr<Evento>> run();  // Executa o evento,
                                                 // retornando os eventos que
                                                 // deverão ser adicionados a
                                                 // lista ordenada de eventos
	void print();  // Imprime o evento em stdout
};

#endif  // EVENTO_HPP
