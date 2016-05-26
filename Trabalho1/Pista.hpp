#ifndef PISTA_HPP
#define PISTA_HPP

#include "FilaEnc.hpp"
#include "Carro.hpp"
#include "Semaforo.hpp"

/**
 * @brief      Classe que representa uma pista
 */
class Pista {
protected:
	Semaforo& semaforo;  // Referência para o semáforo no qual essa pista termina
	Direcao direcao;  // Direção de rolamento
	FilaEnc<Carro> fila;  // Fila de carros
	int tamanho = 0, velocidade = 0; // Tamanho e velocidade
	int entraram = 0, sairam = 0;  // Carros que entraram e sairam na instancia atual
	static int totalEntraram, totalSairam;  // Carros que entraram e sairam em
	                                        // todas as instâncias de Pista

public:
	Pista(Semaforo& s, Direcao d, int tam, int vel);  // Construtor da Pista
	void adiciona(Carro c);  // Adiciona um carro no inicio
	Carro retira();  // Retira um carro do final
	bool estaVazia();  // Testa se a pista está vazia
	virtual Pista& moveCarro(); // Move um carro para a próxima pista
	int tempoParaPercorrer() const;  // Tempo para percorrer a pista atual
	int quantosEntraram() const;  // Quantos carros entraram
	int quantosSairam() const;  // Quantos carros sairam
	int estaoDentro() const;  // Quantos carros estão dentro
	static int totalQuantosEntraram();  // Quantos carros entraram em todas as pista
	static int totalQuantosSairam();  // Quantos carros sairam em todas as pista
};

/**
 * @brief      Classe que representa uma Fonte, pista que pode criar carros
 */
class Fonte : public Pista {
private:
	int frequenciaFixa = 0, frequenciaVariavel = 0;
	Pista &saidaDir, &saidaReto, &saidaEsq;

public:
	Fonte(Semaforo& s, Direcao d, int tam, int vel, int fFixa, int fVar,
		Pista& sDir, Pista& sReto, Pista& sEsq);

	void criaCarro();  // Cria um carro na pista atual
	virtual Pista& moveCarro();
	int tempoProximoEvento(int tempo);
};

/**
 * @brief      Classe que representa uma pista central (nem sumidouro, nem fonte)
 */
class PistaCentro : public Pista {
private:
	Pista &saidaDir, &saidaReto, &saidaEsq;

public:
	PistaCentro(Semaforo& s, Direcao d, int tam, int vel,
		Pista& sDir, Pista& sReto, Pista& sEsq);
	virtual Pista& moveCarro();
};

/**
 * @brief      Classe que representa um Sumidouro, classe que pode retirar carros do sistema
 */
class Sumidouro : public Pista {
public:
	Sumidouro(Semaforo& s, Direcao d, int tam, int vel);
};

#endif  // PISTA_HPP