#ifndef ARVORE_AVL_HPP
#define ARVORE_AVL_HPP
#include "NoAVL.hpp"

template <typename T>
class ArvoreAVL  {
 private:
 	NoAVL<T>* root;


 public:
	ArvoreAVL() = default;

	~ArvoreAVL() {
		delete root;
	}

	void inserir(T dado) {
		if (!root) {
			root = new NoAVL(dado);
		} else {
			root = root->inserir(dado, root);
		}
	}

	void remover(T dado) {
		if (!root) {
			throw std::runtime_error("error in ArvoreAVL::remover: arvore vazia");
		}

		root = root->remover(root, dado);
	}

	T busca(T dado) {
		return *root->busca(dado, root);
	}

};