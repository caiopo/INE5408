#include "Evento.hpp"
#include "ListaOrdenada.hpp"
#include "Semaforo.hpp"
#include "Pista.hpp"
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <memory>

// Lista ordenada que contém ponteiros para Eventos
ListaOrdenada<std::shared_ptr<Evento>> eventos;

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
PistaCentro C1oeste(semaforo1, Direcao::OESTE, 300, 60, N1norte, O1oeste, S1sul);
PistaCentro C1leste(semaforo2, Direcao::LESTE, 300, 60, S2sul, L1leste, N2norte);

// Fontes do semaforo1
Fonte N1sul(semaforo1, Direcao::SUL, 500, 60, 20, 5, O1oeste, S1sul, C1leste);
Fonte O1leste(semaforo1, Direcao::LESTE, 2000, 80, 10, 2, S1sul, C1leste, N1norte);
Fonte S1norte(semaforo1, Direcao::NORTE, 500, 60, 30, 7, C1leste, N1norte, O1oeste);

// Fontes do semaforo2
Fonte N2sul(semaforo2, Direcao::SUL, 500, 40, 20, 5, O1oeste, S2sul, L1leste);
Fonte L1oeste(semaforo2, Direcao::OESTE, 400, 30, 10, 2, N2norte, C1oeste, S2sul);
Fonte S2norte(semaforo2, Direcao::NORTE, 500, 40, 60, 15, L1leste, N2norte, C1oeste);

/**
 * @brief      Imprime o relatório de todas as pistas no stdout
 */
void relatorio() {
	std::cout << "Relatório:\n" <<

	"\nFontes do Semáforo 1\n" <<

	"N1sul { Entraram: "   << N1sul.quantosEntraram() <<
	" Sairam: " 		   << N1sul.quantosSairam() <<
	" Estão dentro: " 	   << N1sul.estaoDentro() << " }\n"

	"O1leste { Entraram: " << O1leste.quantosEntraram() <<
	" Sairam: " 		   << O1leste.quantosSairam() <<
	" Estão dentro: " 	   << O1leste.estaoDentro() << " }\n"

	"S1norte { Entraram: " << S1norte.quantosEntraram() <<
	" Sairam: " 		   << S1norte.quantosSairam() <<
	" Estão dentro: " 	   << S1norte.estaoDentro() << " }\n"


	"\nFontes do Semáforo 2\n" <<

	"N2sul { Entraram: "   << N2sul.quantosEntraram() <<
	" Sairam: " 		   << N2sul.quantosSairam() <<
	" Estão dentro: " 	   << N2sul.estaoDentro() << " }\n"

	"L1oeste { Entraram: " << L1oeste.quantosEntraram() <<
	" Sairam: " 		   << L1oeste.quantosSairam() <<
	" Estão dentro: " 	   << L1oeste.estaoDentro() << " }\n"

	"S2norte { Entraram: " << S2norte.quantosEntraram() <<
	" Sairam: " 		   << S2norte.quantosSairam() <<
	" Estão dentro: " 	   << S2norte.estaoDentro() << " }\n"


	"\nPistas centrais\n" <<

	"C1oeste { Entraram: " << C1oeste.quantosEntraram() <<
	" Sairam: " 		   << C1oeste.quantosSairam() <<
	" Estão dentro: " 	   << C1oeste.estaoDentro() << " }\n"

	"C1leste { Entraram: " << C1leste.quantosEntraram() <<
	" Sairam: " 		   << C1leste.quantosSairam() <<
	" Estão dentro: " 	   << C1leste.estaoDentro() << " }\n"


	"\nSumidouros do Semáforo 1\n" <<

	"O1oeste { Entraram: " << O1oeste.quantosEntraram() <<
	" Sairam: " 		   << O1oeste.quantosSairam() <<
	" Estão dentro: " 	   << O1oeste.estaoDentro() << " }\n"

	"N1norte { Entraram: " << N1norte.quantosEntraram() <<
	" Sairam: " 		   << N1norte.quantosSairam() <<
	" Estão dentro: " 	   << N1norte.estaoDentro() << " }\n"

	"S1sul { Entraram: "   << S1sul.quantosEntraram() <<
	" Sairam: " 		   << S1sul.quantosSairam() <<
	" Estão dentro: " 	   << S1sul.estaoDentro() << " }\n"


	"\nSumidouros do Semáforo 2\n" <<

	"N2norte { Entraram: " << N2norte.quantosEntraram() <<
	" Sairam: " 		   << N2norte.quantosSairam() <<
	" Estão dentro: " 	   << N2norte.estaoDentro() << " }\n"

	"L1leste { Entraram: " << L1leste.quantosEntraram() <<
	" Sairam: " 		   << L1leste.quantosSairam() <<
	" Estão dentro: " 	   << L1leste.estaoDentro() << " }\n"

	"S2sul { Entraram: "   << S2sul.quantosEntraram() <<
	" Sairam: " 		   << S2sul.quantosSairam() <<
	" Estão dentro: " 	   << S2sul.estaoDentro() << " }\n\n"


	"Total { Entraram: " << Pista::totalQuantosEntraram() <<
	" Sairam: " 		 << Pista::totalQuantosSairam() <<
	" Estão dentro: "
	<< Pista::totalQuantosEntraram() - Pista::totalQuantosSairam() << " }\n"

	<< std::endl;
}

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

	eventos.adiciona(std::make_shared<EventoCriarCarro>(0, N1sul));
	eventos.adiciona(std::make_shared<EventoCriarCarro>(0, O1leste));
	eventos.adiciona(std::make_shared<EventoCriarCarro>(0, S1norte));
	eventos.adiciona(std::make_shared<EventoCriarCarro>(0, N2sul));
	eventos.adiciona(std::make_shared<EventoCriarCarro>(0, S2norte));

	eventos.adiciona(std::make_shared<EventoAbrirSemaforo>(0, "S1", semaforo1, frequenciaSemaforo));
	eventos.adiciona(std::make_shared<EventoAbrirSemaforo>(0, "S2", semaforo2, frequenciaSemaforo));

	eventos.print();

	std::cout << std::endl << std::endl;

	int tempoAtual = 0;

	while (tempoAtual <= tempoSimulacao) {
		auto eventoAtual = eventos.retira();
		tempoAtual = eventoAtual->getTempo();
		std::cout << "Iniciando evento. Tempo atual: " << tempoAtual << "  {\n";
		std::cout << "Evento atual: ";

		eventoAtual->print();

		auto vec = eventoAtual->run();

		for (auto i = vec.begin(); i != vec.end(); ++i)
			eventos.adiciona(*i);

		// eventos.print();

		std::cout << "}\n\n";
	}

	relatorio();
}