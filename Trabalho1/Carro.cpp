#include "Carro.hpp"
#include "cstdlib"

Carro::Carro():
	size(TAM_FIXO + TAM_VAR * rand() / RAND_MAX) {}

int Carro::getSize() {
	return size;
}