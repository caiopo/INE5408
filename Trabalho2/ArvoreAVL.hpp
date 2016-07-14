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
		std::ifstream input(filename, std::ios::in | std::ios::binary);

		if (!input) {
			throw std::runtime_error("ArvoreAVL::ctor: could not open file");
		}

		T obj;

		while (input.good()) {
			input.read((char*) &obj, sizeof(T));

			try {
				inserir(obj);
			} catch (std::runtime_error& err) {
				// std::cout << "Chave repetida!" << std::endl;
				break;
			}
		}

		input.close();
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
			throw std::runtime_error("ArvoreAVL::remover: arvore vazia");
		}

		root = root->remover(root, dado);
	}

	T* busca(T& dado) {
		return root->busca(dado, root);
	}

	void saveOnDisk(const std::string filename) {
		std::ofstream output(filename, std::ios::out | std::ios::binary);

		if (!output) {
			throw std::runtime_error("ArvoreAVL::saveOnDisk: could not open file");
		}

		auto vec = emOrdem();

		for (auto i = vec.begin(); i != vec.end(); ++i) {

			T obj = *(*i)->getDado();

			output.write((char*) &obj, sizeof(T));
		}

		output.close();
	}

	std::vector<NoAVL<T>*> emOrdem() {
		root->elementos.clear();
		root->emOrdem(root);
		return root->getElementos();
	}

	std::vector<NoAVL<T>*> preOrdem() {
		root->elementos.clear();
		root->preOrdem(root);
		return root->getElementos();
	}

	std::vector<NoAVL<T>*> posOrdem() {
		root->elementos.clear();
		root->posOrdem(root);
		return root->getElementos();
	}

};

#endif  // ARVORE_AVL_HPP
