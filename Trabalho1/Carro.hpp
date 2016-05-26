#ifndef CARRO_HPP
#define CARRO_HPP

/**
 * @brief      Classe que representa um carro
 */
class Carro {
private:
	int size;  // Tamanho do carro
	const int TAM_FIXO = 5, TAM_VAR = 4;  // Tamanho fixo e variável
public:
	Carro();  // Construtor do carro
	int getSize();  // Retorna o tamanho do carro
};

#endif  // CARRO_HPP