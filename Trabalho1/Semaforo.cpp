#include "Semaforo.hpp"

Semaforo::inverter() {
	if (estado == Estado::VERTICAL)
		estado = Estado::HORIZONTAL;
	else
		estado = Estado::VERTICAL;
}