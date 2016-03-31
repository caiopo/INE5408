// Copyright 2016 Caio Pereira Oliveira

#ifndef FILA_HPP
#define FILA_HPP

#include <stdexcept>


template <typename T>
class Fila {
 private:
	static const int DEFAULT_SIZE = 10;
	T* dados;
	int tam, inicio, fim;

 public:
	explicit Fila(int t = DEFAULT_SIZE);
	void inclui(T dado);
	T retira();
	T ultimo();
	int getUltimo();
	bool filaCheia();
	bool filaVazia();
	void inicializaFila();
};

template <typename T>
Fila<T>::Fila(int t) {
	dados = new T[t];
	tam = t;
	inicio = -1;
	fim = -1;
}

template <typename T>
void Fila<T>::inclui(T dado) {
	if(filaCheia())
		throw std::runtime_error("fila cheia");

	fim = (fim+1) % tam;

	dados[fim] = dado;
}

template <typename T>
T Fila<T>::retira() {
	if(filaVazia())
		throw std::runtime_error("fila vazia");

	inicio = (inicio+1) % tam;

	return dados[inicio];
}

template <typename T>
T Fila<T>::ultimo() {
	if(filaVazia())
		throw std::runtime_error("fila vazia");
	return dados[fim];
}

template <typename T>
int Fila<T>::getUltimo() {
	int size = abs(fim-inicio);

	if(size == 0)
		throw std::runtime_error("fila vazia");
	else
		return size-1;
}

template <typename T>
bool Fila<T>::filaCheia() {
	return abs(fim-inicio) == tam;
}

template <typename T>
bool Fila<T>::filaVazia() {
	return inicio == fim;
}

template <typename T>
void Fila<T>::inicializaFila() {
	inicio = -1;
	fim = -1;
}

#endif  // FILA_HPP
