#include "Lista.hpp"
#include <exception>
#include <iostream>

#define DEFAULT_SIZE 10

template<typename T>
Lista<T>::Lista() {
	tamanho = DEFAULT_SIZE;
	dados = new T[tamanho];
	ultimo = -1;
}

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

	ultimo++;
	dados[ultimo] = dado;

}

template<typename T>
void Lista<T>::adicionaNoInicio(T dado) {

}

template<typename T>
void Lista<T>::adicionaNaPosicao(T dado, int posicao) {

}

template<typename T>
void Lista<T>::adicionaEmOrdem(T dado) {

}

template<typename T>
T Lista<T>::retira() {
	if(listaVazia())
		throw std::runtime_error("lista vazia");

	return dados[ultimo--];
}

template<typename T>
T Lista<T>::retiraDoInicio() {

}

template<typename T>
T Lista<T>::retiraDaPosicao(int posicao) {
	if(posicao >= tamanho || posicao < 0)
		throw std::invalid_argument("posicao must be smaller than tamanho and greater than zero");

	for (int i = 0; i < count; ++i) {

	}

}

template<typename T>
T Lista<T>::retiraEspecifico(T dado) {
	int pos = posicao(dado);

	if(pos == -1)
		throw std::invalid_argument("dado not found");

	return retiraDaPosicao(pos);
}

template<typename T>
int Lista<T>::posicao(T dado) {
	for (int i = 0; i <= ultimo; ++i) {
		if(dados[i] == dado)
			return i;
	}

	return -1;
}

template<typename T>
bool Lista<T>::contem(T dado) {
	for (int i = 0; i <= ultimo; ++i) {
		if(dados[i] == dado)
			return true;
	}

	return false;
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


int main() {
	Lista<int> l(5);
	l.print();

	for (int i = 0; i < 6; ++i) {
		l.adiciona(i);
	}
	
	l.print();
}


// template<typename T>
// class Lista {
//  public:
// 	Lista();
// 	explicit Lista(int tam);
// 	void adiciona(T dado);
// 	void adicionaNoInicio(T dado);
// 	void adicionaNaPosicao(T dado, int posicao);
// 	void adicionaEmOrdem(T dado);
// 	T retira();
// 	T retiraDoInicio();
// 	T retiraDaPosicao(int posicao);
// 	T retiraEspecifico(T dado);
// 	int posicao(T dado);
// 	bool contem(T dado);
// 	bool igual(T dado1, T dado2);
// 	bool maior(T dado1, T dado2);
// 	bool menor(T dado1, T dado2);
// 	bool listaCheia();
// 	bool listaVazia();
// 	void destroiLista();
// };

