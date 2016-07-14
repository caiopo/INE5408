#ifndef REGISTRO_HPP
#define REGISTRO_HPP

#include <cstring>

struct ManPage {
	char comando[100];
	char conteudo[140000];

	inline bool operator<(const ManPage& rhs) const {
		return strcmp(comando, rhs.comando) < 0;
	}

	inline bool operator>(const ManPage& rhs) const {
		return strcmp(comando, rhs.comando) > 0;
	}

	inline bool operator==(const ManPage& rhs) const {
		return strcmp(comando, rhs.comando) == 0;
	}

	inline bool operator!=(const ManPage& rhs) const {
		return !(*this == rhs);
	}
};

struct ManPagePtr {
	char comando[100];
	std::streampos pos = 0;

	inline bool operator<(const ManPagePtr& rhs) const {
		return strcmp(comando, rhs.comando) < 0;
	}

	inline bool operator>(const ManPagePtr& rhs) const {
		return strcmp(comando, rhs.comando) > 0;
	}

	inline bool operator==(const ManPagePtr& rhs) const {
		return strcmp(comando, rhs.comando) == 0;
	}

	inline bool operator!=(const ManPagePtr& rhs) const {
		return !(*this == rhs);
	}
};

struct Word {
	char word[100];
	unsigned int index = 0;
	std::streampos pos[5650];

	void add(std::streampos _pos) {
		pos[index] = _pos;
		++index;
	}

	inline bool operator<(const Word& rhs) const {
		return strcmp(word, rhs.word) < 0;
	}

	inline bool operator>(const Word& rhs) const {
		return strcmp(word, rhs.word) > 0;
	}

	inline bool operator==(const Word& rhs) const {
		return strcmp(word, rhs.word) == 0;
	}

	inline bool operator!=(const Word& rhs) const {
		return !(*this == rhs);
	}
};

struct WordPtr {
	char word[100];
	std::streampos pos = 0;

	inline bool operator<(const WordPtr& rhs) const {
		return strcmp(word, rhs.word) < 0;
	}

	inline bool operator>(const WordPtr& rhs) const {
		return strcmp(word, rhs.word) > 0;
	}

	inline bool operator==(const WordPtr& rhs) const {
		return strcmp(word, rhs.word) == 0;
	}

	inline bool operator!=(const WordPtr& rhs) const {
		return !(*this == rhs);
	}
};

#endif  // REGISTRO_HPP
