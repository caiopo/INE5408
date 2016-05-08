#ifndef SEMAFORO_HPP
#define SEMAFORO_HPP

class Semaforo {
private:
	enum class Estado { VERTICAL, HORIZONTAL };

	Estado estado = Estado::VERTICAL;

public:
	Semaforo() =  default;
	void inverter();
};

#endif  // SEMAFORO_HPP