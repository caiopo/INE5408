// Copyright 2016 Caio Pereira Oliveira

#ifndef PILHA_HPP
#define PILHA_HPP

#include <stdexcept>

template<typename T>
class Pilha {
	private:
		int MAXPILHA;
		int size;
		T* dados;

	public:
		Pilha();
		Pilha<T>(int t);
		void empilha(T dado);
		T desempilha();
		T topo();
		int getPosTopo();
		void limparPilha();
		bool PilhaVazia();
		bool PilhaCheia();
};

template <typename T>
Pilha<T>::Pilha() {
	MAXPILHA = 10;
	dados = new T[10];
	size = -1;
}

template <typename T>
Pilha<T>::Pilha(int t) {
	MAXPILHA = t;
	dados = new T[t];
	size = -1;
}

template <typename T>
void Pilha<T>::empilha(T dado) {
	if(PilhaCheia())
		throw std::runtime_error("pilha cheia");

	size++;
	dados[size] = dado;
}

template <typename T>
T Pilha<T>::desempilha() {
	if(PilhaVazia())
		throw std::runtime_error("pilha vazia");

	size--;
	return dados[size+1];
}

template <typename T>
T Pilha<T>::topo() {
	if(PilhaVazia())
		throw std::runtime_error("pilha vazia");

	return dados[size];
}

template <typename T>
int Pilha<T>::getPosTopo() {
	if(size == -1)
		throw std::runtime_error("topo inexistente: pilha vazia");
	return size;
}

template <typename T>
void Pilha<T>::limparPilha() {
	size = -1;
}


template <typename T>
bool Pilha<T>::PilhaCheia() {
	return size == MAXPILHA-1;
}

template <typename T>
bool Pilha<T>::PilhaVazia() {
	return size == -1;
}

#endif  // PILHA_HPP
