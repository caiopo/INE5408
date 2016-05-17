#include "ListaOrdenada.hpp"
#include "Semaforo.hpp"
#include "Pista.hpp"
#include <cstdlib>
#include <ctime>
#include <iostream>


// ListaOrdenada de eventos
ListaOrdenada eventos;

// Semáforos
Semaforo semaforo1(NumSemaforo::S1), semaforo2(NumSemaforo::S2);

// Sumidouros do semaforo1
Sumidouro O1oeste(Direcao::OESTE, 2000, 80);
Sumidouro N1norte(Direcao::NORTE, 500, 60);
Sumidouro S1sul(Direcao::SUL, 500, 60);

// Sumidouros do semaforo2
Sumidouro N2norte(Direcao::NORTE, 500, 40);
Sumidouro L1leste(Direcao::LESTE, 400, 30);
Sumidouro S2sul(Direcao::SUL, 500, 40);

// Pistas centrais
Pista C1oeste(Direcao::OESTE, 300, 60);
Pista C1leste(Direcao::LESTE, 300, 60);

// Fontes do semaforo1
Fonte N1sul(Direcao::SUL, 500, 60, 20, 5, O1oeste, S1sul, C1leste);
Fonte O1leste(Direcao::LESTE, 2000, 80, 10, 2, S1sul, C1leste, N1norte);
Fonte S1norte(Direcao::NORTE, 500, 60, 30, 7, C1leste, N1norte, O1oeste);

// Fontes do semaforo2
Fonte N2sul(Direcao::SUL, 500, 40, 20, 5, O1oeste, S2sul, L1leste);
Fonte L1oeste(Direcao::OESTE, 400, 30, 10, 2, N2norte, C1oeste, S2sul);
Fonte S2norte(Direcao::NORTE, 500, 40, 60, 15, L1leste, N2norte, C1oeste);

int tempoSimulacao, frequenciaSemaforo;

int main(int argc, char const *argv[]) {
	srand(time(NULL));

	if (argc != 3) {
		std::cout << "parâmetros incorretos, esperava por: <tempoSimulacao> <frequenciaSemaforo>" << std::endl;
		exit(1);
	}

	tempoSimulacao = atoi(argv[1]);
	frequenciaSemaforo = atoi(argv[2]);

	if (tempoSimulacao <= 0 || frequenciaSemaforo <= 0) {
		std::cout << "tempoSimulacao or frequenciaSemaforo inválidos" << std::endl;
		exit(1);
	}


	int tempoAtual = 0;

	while (tempoAtual <= tempoSimulacao) {
		Evento eventoAtual = eventos.retira();
		tempoAtual = eventoAtual.getTempo();




	}




}