#ifndef CARRO_HPP
#define CARRO_HPP

class Carro {
private:
	int size;
	const int TAM_FIXO = 5, TAM_VAR = 4;
public:
	Carro();
	int getSize();
};

#endif  // CARRO_HPP