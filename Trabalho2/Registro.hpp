#ifndef REGISTRO_HPP
#define REGISTRO_HPP

#include <cstring>

struct Registro {
	char comando[100];
	char conteudo[140000];

	bool operator<(const Registro& rhs) {
		return strcmp(comando, rhs.comando) < 0;
	}

	bool operator>(const Registro& rhs) {
		return strcmp(comando, rhs.comando) > 0;
	}

	bool operator==(const Registro& rhs) {
		return strcmp(comando, rhs.comando) == 0;
	}
};

struct Entrada {
	char comando[100];
	std::streampos pos;

	bool operator<(const Registro& rhs) {
		return strcmp(comando, rhs.comando) < 0;
	}

	bool operator>(const Registro& rhs) {
		return strcmp(comando, rhs.comando) > 0;
	}

	bool operator==(const Registro& rhs) {
		return strcmp(comando, rhs.comando) == 0;
	}
};

#endif  // REGISTRO_HPP
