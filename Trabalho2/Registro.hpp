#ifndef REGISTRO_HPP
#define REGISTRO_HPP

#include <cstring>

struct Registro {
	char comando[100];
	char conteudo[140000];

	bool operator<(const Registro& rhs) const {
		return strcmp(comando, rhs.comando) < 0;
	}

	bool operator>(const Registro& rhs) const {
		return strcmp(comando, rhs.comando) > 0;
	}

	bool operator==(const Registro& rhs) const {
		return strcmp(comando, rhs.comando) == 0;
	}
};

struct ManpageEntry {
	char comando[100];
	std::streampos pos;

	bool operator<(const ManpageEntry& rhs) const {
		return strcmp(comando, rhs.comando) < 0;
	}

	bool operator>(const ManpageEntry& rhs) const {
		return strcmp(comando, rhs.comando) > 0;
	}

	bool operator==(const ManpageEntry& rhs) const {
		return strcmp(comando, rhs.comando) == 0;
	}
};

struct Word {
	char word[50];
	unsigned int index = 0;
	std::streampos pos[5650];

	void add(std::streampos _pos) {
		pos[index] = _pos;
		++index;
	}

	bool operator<(const Word& rhs) const {
		return strcmp(word, rhs.word) < 0;
	}

	bool operator>(const Word& rhs) const {
		return strcmp(word, rhs.word) > 0;
	}

	bool operator==(const Word& rhs) const {
		return strcmp(word, rhs.word) == 0;
	}
};

struct WordPtr {
	char word[50];
	std::streampos pos = 0;

	bool operator<(const WordPtr& rhs) const {
		return strcmp(word, rhs.word) < 0;
	}

	bool operator>(const WordPtr& rhs) const {
		return strcmp(word, rhs.word) > 0;
	}

	bool operator==(const WordPtr& rhs) const {
		return strcmp(word, rhs.word) == 0;
	}
};

#endif  // REGISTRO_HPP
