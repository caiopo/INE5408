// Copyright 2016 Caio Pereira Oliveira

#ifndef LISTA_HPP
#define LISTA_HPP

#include <stdexcept>

template<typename T>
class Lista {
 private:
	static const int DEFAULT_SIZE = 10;
	T* dados;
	int ultimo;
	int tamanho;

 public:
	explicit Lista(int tam = DEFAULT_SIZE);
	void adiciona(T dado);
	void adicionaNoInicio(T dado);
	void adicionaNaPosicao(T dado, int posicao);
	void adicionaEmOrdem(T dado);
	T retira();
	T retiraDoInicio();
	T retiraDaPosicao(int posicao);
	T retiraEspecifico(T dado);
	int posicao(T dado);
	bool contem(T dado);
	bool igual(T dado1, T dado2);
	bool maior(T dado1, T dado2);
	bool menor(T dado1, T dado2);
	bool listaCheia();
	bool listaVazia();
	void destroiLista();
	void print();
};

template<typename T>
Lista<T>::Lista(int tam) {
	tamanho = tam;
	dados = new T[tamanho];
	ultimo = -1;
}

template<typename T>
void Lista<T>::adiciona(T dado) {
	if(listaCheia())
		throw std::runtime_error("lista cheia");

	dados[++ultimo] = dado;
}

template<typename T>
void Lista<T>::adicionaNoInicio(T dado) {
	adicionaNaPosicao(dado, 0);
}

template<typename T>
void Lista<T>::adicionaNaPosicao(T dado, int posicao) {
	if (listaCheia())
		throw std::runtime_error("lista cheia");

	ultimo++;

	for (int i = ultimo; i > posicao; --i) {
		dados[i] = dados[i-1];
	}

	dados[posicao] = dado;
}

template<typename T>
void Lista<T>::adicionaEmOrdem(T dado) {
	int pos = 0;

	while (pos <= ultimo && dado > dados[pos])
		pos++;

	adicionaNaPosicao(dado, pos);
}

template<typename T>
T Lista<T>::retira() {
	if (listaVazia())
		throw std::runtime_error("lista vazia");

	ultimo--;
	return dados[ultimo+1];
}

template<typename T>
T Lista<T>::retiraDoInicio() {
	return retiraDaPosicao(0);
}

template<typename T>
T Lista<T>::retiraDaPosicao(int posicao) {
	if (listaVazia())
		throw std::runtime_error("lista vazia");

	if (posicao >= tamanho || posicao < 0)
		throw std::invalid_argument("posicao must be smaller than tamanho and greater than zero");

	T removido = dados[posicao];

	for (int i = posicao; i < ultimo; ++i) {
		dados[i] = dados[i+1];
	}

	ultimo--;

	return removido;


}

template<typename T>
T Lista<T>::retiraEspecifico(T dado) {
	int pos = posicao(dado);

	return retiraDaPosicao(pos);
}

template<typename T>
int Lista<T>::posicao(T dado) {
	for (int i = 0; i <= ultimo; ++i)
		if (dados[i] == dado)
			return i;

	throw std::runtime_error("dado não encontrado");
}

template<typename T>
bool Lista<T>::contem(T dado) {
	try {
		posicao(dado);
	} catch (std::runtime_error& err) {
		return false;
	}

	return true;

}

template<typename T>
bool Lista<T>::igual(T dado1, T dado2) {
	return dado1 == dado2;
}

template<typename T>
bool Lista<T>::maior(T dado1, T dado2) {
	return dado1 > dado2;
}

template<typename T>
bool Lista<T>::menor(T dado1, T dado2) {
	return dado1 < dado2;
}

template<typename T>
bool Lista<T>::listaCheia() {
	return ultimo == tamanho-1;
}

template<typename T>
bool Lista<T>::listaVazia() {
	return ultimo == -1;
}

template<typename T>
void Lista<T>::destroiLista() {
	ultimo = -1;
}

template<typename T>
void Lista<T>::print() {
	for (int i = 0; i < tamanho; ++i) {
		std::cout << dados[i] << " ";
	}

	std::cout << std::endl;
}

#endif  // LISTA_HPP
