#ifndef LISTAORDENADA_HPP
#define LISTAORDENADA_HPP

#include "ListaEnc.hpp"

/**
 * @brief      Classe que implementa uma Lista Ordenada
 *
 * @tparam     T     Parâmetro de Template
 */
template<typename T>
class ListaOrdenada {
private:
	ListaEnc<T> lista;
public:
	ListaOrdenada() = default;
	void adiciona(T e);
	T retira();
	bool estaVazia();
	int getSize();
	void print();
};

/**
 * @brief      Adiciona mantendo a ordenação da lista
 *
 * @param[in]  e     Dado a ser adicionado
 *
 * @tparam     T     Parâmetro de template
 */
template<typename T>
void ListaOrdenada<T>::adiciona(T e) {
	lista.adicionaEmOrdem(e);
}

/**
 * @brief      Retira um elemento do inicio da lista
 *
 * @tparam     T     Parâmetro de template
 *
 * @return     Elemento retirado
 */
template<typename T>
T ListaOrdenada<T>::retira() {
	return lista.retiraDoInicio();
}

/**
 * @brief      Testa se a lista está vazia
 *
 * @tparam     T     Parâmetro de templates
 *
 * @return     true se a lista estiver vazia, false senão
 */
template<typename T>
bool ListaOrdenada<T>::estaVazia() {
	return lista.listaVazia();
}

/**
 * @brief      Retorna o tamanho da lista
 *
 * @tparam     T     Parâmetro de template
 *
 * @return     O Tamanho da lista
 */
template<typename T>
int ListaOrdenada<T>::getSize() {
	return lista.getSize();
}

/**
 * @brief      Imprime a lista no stdout
 *
 * @tparam     T     Parâmetro de template
 */
template<typename T>
void ListaOrdenada<T>::print() {
	lista.print();
}

#endif  // LISTAORDENADA_HPP
