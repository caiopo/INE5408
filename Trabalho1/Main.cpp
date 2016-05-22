#include "ListaOrdenada.hpp"
#include "Semaforo.hpp"
#include "Pista.hpp"
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <memory>

// ListaOrdenada de eventos
ListaOrdenada<std::shared_ptr<Evento>> eventos;
// ListaEnc<std::unique_ptr<Evento>> eventos;

// Semáforos
Semaforo semaforo1(NumSemaforo::S1), semaforo2(NumSemaforo::S2);

// Sumidouros do semaforo1
Sumidouro O1oeste(semaforo1, Direcao::OESTE, 2000, 80);
Sumidouro N1norte(semaforo1, Direcao::NORTE, 500, 60);
Sumidouro S1sul(semaforo1, Direcao::SUL, 500, 60);

// Sumidouros do semaforo2
Sumidouro N2norte(semaforo2, Direcao::NORTE, 500, 40);
Sumidouro L1leste(semaforo2, Direcao::LESTE, 400, 30);
Sumidouro S2sul(semaforo2, Direcao::SUL, 500, 40);

// Pistas centrais
Pista C1oeste(semaforo1, Direcao::OESTE, 300, 60);
Pista C1leste(semaforo2, Direcao::LESTE, 300, 60);

// Fontes do semaforo1
Fonte N1sul(semaforo1, Direcao::SUL, 500, 60, 20, 5, O1oeste, S1sul, C1leste);
Fonte O1leste(semaforo1, Direcao::LESTE, 2000, 80, 10, 2, S1sul, C1leste, N1norte);
Fonte S1norte(semaforo1, Direcao::NORTE, 500, 60, 30, 7, C1leste, N1norte, O1oeste);

// Fontes do semaforo2
Fonte N2sul(semaforo2, Direcao::SUL, 500, 40, 20, 5, O1oeste, S2sul, L1leste);
Fonte L1oeste(semaforo2, Direcao::OESTE, 400, 30, 10, 2, N2norte, C1oeste, S2sul);
Fonte S2norte(semaforo2, Direcao::NORTE, 500, 40, 60, 15, L1leste, N2norte, C1oeste);

int tempoSimulacao, frequenciaSemaforo;

int main(int argc, char const *argv[]) {
	srand(time(0));

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

	std::cout << eventos.getSize() << std::endl;

	eventos.adiciona(std::make_shared<EventoCriarCarro>(0, N1sul));

	eventos.adiciona(std::make_shared<EventoAbrirSemaforo>(0, "s2", semaforo2, frequenciaSemaforo));
	eventos.adiciona(std::make_shared<EventoAbrirSemaforo>(1, "s1", semaforo1, frequenciaSemaforo));

	// eventos.adiciona

	std::cout << eventos.getSize() << std::endl;

	int tempoAtual = 0;

	while (tempoAtual <= tempoSimulacao) {
		auto eventoAtual = eventos.retira();
		std::cout << "Iniciando ciclo. Tempo atual: " << tempoAtual << "  {\n";
		tempoAtual = eventoAtual->getTempo();

		auto vec = eventoAtual->run();

		for (auto i = vec.begin(); i != vec.end(); ++i)
			eventos.adiciona(*i);

		std::cout << "}\n";
	}
}