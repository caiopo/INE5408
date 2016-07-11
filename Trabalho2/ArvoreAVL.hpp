#ifndef ARVORE_AVL_HPP
#define ARVORE_AVL_HPP
#include "NoAVL.hpp"
#include <iostream>
#include <fstream>

template <typename T>
class ArvoreAVL {
 private:
	NoAVL<T>* root = nullptr;

 public:
	ArvoreAVL() = default;

	ArvoreAVL(const std::string filename) {
		std::ifstream input(filename.c_str(),
			std::ios::in | std::ios::binary);

		T obj;

		while (input.good()) {
			input.read((char*) &obj, sizeof(T));

			inserir(obj);
		}
	}

	~ArvoreAVL() {
		delete root;
	}

	void inserir(T dado) {
		if (!root) {
			root = new NoAVL<T>(dado);
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

	void saveOnDisk(const std::string filename) {
		std::ofstream output(filename.c_str(),
			std::ios::out | std::ios::binary);

		auto vec = preOrdem();

		for (auto i = vec.begin(); i != vec.end(); ++i) {

			T obj = *(*i)->getDado();

			output.write((char*) &obj, sizeof(T));
		}
	}

	std::vector<NoAVL<T>*> emOrdem() {
		root->getElementos().clear();
		root->emOrdem(root);
		return root->getElementos();
	}

	std::vector<NoAVL<T>*> preOrdem() {
		root->getElementos().clear();
		root->preOrdem(root);
		return root->getElementos();
	}

	std::vector<NoAVL<T>*> posOrdem() {
		root->getElementos().clear();
		root->posOrdem(root);
		return root->getElementos();
	}

};

#endif  // ARVORE_AVL_HPP
