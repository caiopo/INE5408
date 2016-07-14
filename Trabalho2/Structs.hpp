#ifndef STRUCTS_HPP
#define STRUCTS_HPP

#include <cstring>

/**
 * @brief      Struct que representa uma manpage
 */
struct ManPage {
	char comando[100];       //! string que guarda o comando da manpage
	char conteudo[140000];   //! string que guarda o conteudo da manpage

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

/**
 * @brief      Struct que representa um ponteiro para uma manpage que esta em
 *             disco
 */
struct ManPagePtr {
	char comando[100];        //! string que guarda o comando da manpage
	std::streampos pos = 0;   //! posicao do comando no ManPages.dat

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

/**
 * @brief      Struct que representa uma palavra
 */
struct Word {
	char word[100];            //! string que guarda a palavra

	unsigned int index = 0;    //! int que guarda a quantidade de
	                           //! posicoes validas no vetor pos

	std::streampos pos[5650];  //! array de posicoes das manpages que contem
	                           //!  a palavra atual no ManPages.dat

	/**
	 * @brief      Adiciona uma posicao no array
	 *
	 * @param[in]  _pos  Posicao a ser adicionada
	 */
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

/**
 * @brief      Struct que representa um ponteiro para uma entrada do arquivo
 *             invertido que esta em disco
 */
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

#endif  // STRUCTS_HPP
