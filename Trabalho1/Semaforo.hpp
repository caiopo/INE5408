#ifndef SEMAFORO_HPP
#define SEMAFORO_HPP

enum class Direcao {
	NORTE,
	SUL,
	LESTE,
	OESTE
};

enum class NumSemaforo {
	S1,
	S2
};

class Semaforo {
private:
	Direcao direcao = Direcao::NORTE;
	NumSemaforo num;

public:
	explicit Semaforo(NumSemaforo n);
	void proximoEstado();
	Direcao decidePista(Direcao d);
	bool estaAberto();
	Direcao direcaoAtual();
};

#endif  // SEMAFORO_HPP