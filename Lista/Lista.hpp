// Copyright 2016 Caio Pereira Oliveira

#ifndef LISTA_HPP
#define LISTA_HPP

#include <stdexcept>

/**
 * @brief      Implementa a estrura
 *
 * @tparam     T     Parâmetro de Template
 */
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
};

/**
 * @brief      Construtor da Lista
 *
 * @param[in]  tam   Tamanho inicial da Lista
 *
 * @tparam     T     Parâmetro de Template
 */
template<typename T>
Lista<T>::Lista(int tam) {
	tamanho = tam;
	dados = new T[tamanho];
	ultimo = -1;
}

/**
 * @brief      Adiciona o dado no final da lista
 *
 * @param[in]  dado  Dado a ser adicionado
 *
 * @tparam     T     Parâmetro de template
 */
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

/**
 * @brief      Adiciona o dado na posição
 *
 * @param[in]  dado     Dado a ser adicionado
 * @param[in]  posicao  Posicao para adicionar o dado
 *
 * @tparam     T        Parâmetro de template
 */
template<typename T>
void Lista<T>::adicionaNaPosicao(T dado, int posicao) {
	if (listaCheia())
		throw std::runtime_error("lista cheia");

	if (posicao > ultimo+1 || posicao < 0)
		throw std::runtime_error("posicao must be smaller than "
								"ultimo+1 and greater than zero");

	ultimo++;

	for (int i = ultimo; i > posicao; --i) {
		dados[i] = dados[i-1];
	}

	dados[posicao] = dado;
}

/**
 * @brief      Adiciona
 *
 * @param[in]  dado  Adiciona o elemento mantendo a ordenação
 *
 * @tparam     T     Parâmetro de Template
 */
template<typename T>
void Lista<T>::adicionaEmOrdem(T dado) {
	int pos = 0;

	while (pos <= ultimo && dado > dados[pos])
		pos++;

	adicionaNaPosicao(dado, pos);
}

/**
 * @brief      Retira um elemento do final da lista
 *
 * @tparam     T     Parâmetro de Template
 *
 * @return     O elemento retirado
 */
template<typename T>
T Lista<T>::retira() {
	if (listaVazia())
		throw std::runtime_error("lista vazia");

	ultimo--;
	return dados[ultimo+1];
}

/**
 * @brief      Retira um elemento do inicio da lista
 *
 * @tparam     T     Parâmetro de Template
 *
 * @return     O elemento retirado
 */
template<typename T>
T Lista<T>::retiraDoInicio() {
	return retiraDaPosicao(0);
}

/**
 * @brief      Retira o elemento na posicao
 *
 * @param[in]  posicao  A posição pra retirar o elemento
 *
 * @tparam     T        Parâmetro de Template
 *
 * @return     O elemento retirado
 */
template<typename T>
T Lista<T>::retiraDaPosicao(int posicao) {
	if (listaVazia())
		throw std::runtime_error("lista vazia");

	if (posicao >= ultimo+1 || posicao < 0)
		throw std::runtime_error("posicao must be smaller than "
								"ultimo+1 and greater than zero");

	T removido = dados[posicao];

	for (int i = posicao; i < ultimo; ++i) {
		dados[i] = dados[i+1];
	}

	ultimo--;

	return removido;
}


/**
 * @brief      Retira o elemento dado da lista e o retorna
 *
 * @param[in]  dado  O dado a ser retirado
 *
 * @tparam     T     Parâmetro de Template
 *
 * @return     O dado retirado
 */
template<typename T>
T Lista<T>::retiraEspecifico(T dado) {
	int pos = posicao(dado);

	return retiraDaPosicao(pos);
}

/**
 * @brief      Descobre a posição do dado na lista
 *
 * @param[in]  dado  O dado a ser testado
 *
 * @tparam     T     Parâmetro de Template
 *
 * @return     O um inteiro representando o índice que contém dado
 */
template<typename T>
int Lista<T>::posicao(T dado) {
	for (int i = 0; i <= ultimo; ++i)
		if (dados[i] == dado)
			return i;

	throw std::runtime_error("dado não encontrado");
}

/**
 * @brief      Testa se a lista contém o dado
 *
 * @param[in]  dado  O dado a ser testado
 *
 * @tparam     T     Parâmetro de Template
 *
 * @return     true se dado estiver na lista, se não, false
 */
template<typename T>
bool Lista<T>::contem(T dado) {
	try {
		posicao(dado);
	} catch (std::runtime_error& err) {
		return false;
	}

	return true;
}

/**
 * @brief      Testa se dado1 é igual a dado2
 *
 * @param[in]  dado1  O primeiro dado a ser testado
 * @param[in]  dado2  O segundo dado a ser testanto
 *
 * @tparam     T      Parâmetro de Template
 *
 * @return     true se dado1 == dado2, se não, false
 */
template<typename T>
bool Lista<T>::igual(T dado1, T dado2) {
	return dado1 == dado2;
}

/**
 * @brief      Testa se dado1 é menor que dado2
 *
 * @param[in]  dado1  O primeiro dado a ser testado
 * @param[in]  dado2  O segundo dado a ser testanto
 *
 * @tparam     T      Parâmetro de Template
 *
 * @return     true se dado1 > dado2, se não, false
 */
template<typename T>
bool Lista<T>::maior(T dado1, T dado2) {
	return dado1 > dado2;
}

/**
 * @brief      Testa se dado1 é maior que dado2
 *
 * @param[in]  dado1  O primeiro dado a ser testado
 * @param[in]  dado2  O segundo dado a ser testanto
 *
 * @tparam     T      Parâmetro de Template
 *
 * @return     true se dado1 < dado2, se não, false
 */
template<typename T>
bool Lista<T>::menor(T dado1, T dado2) {
	return dado1 < dado2;
}

/**
 * @brief      Testa se a lista está cheia
 *
 * @tparam     T     Parâmetro de Template
 *
 * @return     true se estiver cheia, se não, false
 */
template<typename T>
bool Lista<T>::listaCheia() {
	return ultimo == tamanho-1;
}

/**
 * @brief      Testa se a lista está vazia
 *
 * @tparam     T     Parâmetro de Template
 *
 * @return     true se estiver vazia, se não, false
 */
template<typename T>
bool Lista<T>::listaVazia() {
	return ultimo == -1;
}

/**
 * @brief      Destrói a Lista, removendo todos os elementos
 *
 * @tparam     T     Parâmetro de Template
 */
template<typename T>
void Lista<T>::destroiLista() {
	ultimo = -1;
}

#endif  // LISTA_HPP
