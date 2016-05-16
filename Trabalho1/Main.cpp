#include "Semaforo.hpp"
#include <cstdlib>
#include <ctime>
#include <iostream>

// ListaOrdenada eventos;

int main() {
	srand(time(NULL));

	Semaforo s(NumSemaforo::S1);

	for (int i = 0; i < 30; ++i)
		std::cout << s.decideDirecao(Direcao::NORTE) << "\n";
}