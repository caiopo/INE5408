#include "Carro.hpp"
#include <cstdlib>
#include <iostream>

Carro::Carro() {
	size = TAM_FIXO + TAM_VAR * (double(rand()) / RAND_MAX);
}

int Carro::getSize() {
	return size;
}