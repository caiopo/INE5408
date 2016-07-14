#ifndef NO_AVL_HPP
#define NO_AVL_HPP
#include <vector>
#include <stdexcept>

template<typename T>
class duplicate_entry_error : public std::runtime_error {
 private:
		T& dupl;

 public:
	duplicate_entry_error(T& _dupl) :
		std::runtime_error("NoAVL::inserir: inserting duplicate key"),
		dupl{_dupl} {}

	T& get() {
		return dupl;
	}
};

template<typename T>
class NoAVL  {
 private:
	int altura = 0;  //!< Representa a altura do nó AVL
	T* dado;
	NoAVL<T>* esquerda = nullptr;
	NoAVL<T>* direita = nullptr;

 public:
	std::vector<NoAVL<T>*> elementos;

	explicit NoAVL(const T& d) {
		dado = new T(d);
	}

	virtual ~NoAVL() {
		delete dado;
		if (esquerda)
			delete esquerda;

		if (direita)
			delete direita;
	}

	int getAltura() {
		return altura;
	}

	std::vector<NoAVL<T>*> getElementos() {
		return elementos;
	}

	NoAVL<T>* getEsquerda() {
		return esquerda;
	}

	NoAVL<T>* getDireita() {
		return direita;
	}

	void atualizaAltura() {
		int altEsq = esquerda ? esquerda->getAltura() : -1;
		int altDir = direita ? direita->getAltura() : -1;

		altura = (altEsq > altDir ? altEsq : altDir) + 1;
	}

	NoAVL<T>* inserir(const T& dado, NoAVL<T>* arv) {
		if (!arv) {
			return new NoAVL(dado);
		}

		if (dado == *arv->dado) {
			throw duplicate_entry_error<T>(*arv->dado);
		} else if (dado < *arv->dado) {
			arv->esquerda = inserir(dado, arv->esquerda);
		} else {
			arv->direita = inserir(dado, arv->direita);
		}

		arv->atualizaAltura();

		int balanceamento = fatorDeBalanceamento(arv);

		if (balanceamento > 1) {
			if (dado > *arv->esquerda->dado) {
				arv->esquerda = rotacaoSimplesEsq(arv->esquerda);
			}

			return rotacaoSimplesDir(arv);
		}

		if (balanceamento < -1) {
			if (dado < *arv->direita->dado) {
				arv->direita = rotacaoSimplesDir(arv->direita);
			}

			return rotacaoSimplesEsq(arv);
		}

		return arv;
	}

	NoAVL<T>* remover(NoAVL<T>* arv, const T& dado) {
		if (!arv) {
			return nullptr;
		}

		if (dado < *arv->dado) {
			arv->esquerda = remover(arv->esquerda, dado);
		} else if (dado > *arv->dado) {
			arv->direita = remover(arv->direita, dado);
		} else {
			NoAVL<T>* temp;
			if (arv->esquerda && arv->direita) {
				temp = minimo(arv->direita);
				*arv->dado = *temp->dado;
				arv->direita = remover(arv->direita, *arv->dado);
			} else {
				if (arv->direita) {
					temp = arv->direita;
					return temp;
				}

				if (arv->esquerda) {
					temp = arv->esquerda;
					return temp;
				}

				delete arv;
				return nullptr;
			}
		}

		if (!arv) {
			return nullptr;
		}

		arv->atualizaAltura();

		int balanceamento = fatorDeBalanceamento(arv);

		if (balanceamento > 1) {
			if (fatorDeBalanceamento(arv->esquerda) < 0) {
				arv->esquerda = rotacaoSimplesEsq(arv->esquerda);
			}

			return rotacaoSimplesDir(arv);
		}

		if (balanceamento < -1) {
			if (fatorDeBalanceamento(arv->direita) > 0) {
				arv->direita = rotacaoSimplesDir(arv->direita);
			}

			return rotacaoSimplesEsq(arv);
		}

		return arv;
	}

	T* busca(const T& dado, NoAVL<T>* arv) {
		while (arv && *arv->dado != dado) {
			if (dado < *arv->dado) {
				arv = arv->esquerda;
			} else {
				arv = arv->direita;
			}
		}

		if (!arv) {
			throw std::runtime_error("NoAVL::busca: dado not found");
		}

		return arv->dado;
	}

	NoAVL<T>* minimo(NoAVL<T>* nodo) {
		return nodo->esquerda ? minimo(nodo->esquerda) : nodo;
	}

	T* getDado() {
		return dado;
	}

	void preOrdem(NoAVL<T>* nodo) {
		if (nodo) {
			elementos.push_back(nodo);
			preOrdem(nodo->esquerda);
			preOrdem(nodo->direita);
		}
	}

	void emOrdem(NoAVL<T>* nodo) {
		if (nodo) {
			emOrdem(nodo->esquerda);
			elementos.push_back(nodo);
			emOrdem(nodo->direita);
		}
	}

	void posOrdem(NoAVL<T>* nodo) {
		if (nodo) {
			posOrdem(nodo->esquerda);
			posOrdem(nodo->direita);
			elementos.push_back(nodo);
		}
	}

private:
	static NoAVL<T>* rotacaoSimplesDir(NoAVL<T>* k2) {
		auto k1 = k2->esquerda;
		k2->esquerda = k1->direita;
		k1->direita = k2;

		/* atualize alturas */
		k2->atualizaAltura();
		k1->atualizaAltura();

		return k1; /* nova raiz da subárvore */
	}

	static NoAVL<T>* rotacaoSimplesEsq(NoAVL<T>* k2) {
		auto k1 = k2->direita;
		k2->direita = k1->esquerda;
		k1->esquerda = k2;

		/* atualize alturas */
		k2->atualizaAltura();
		k1->atualizaAltura();

		return k1; /* nova raiz da subárvore */
	}

	static NoAVL<T>* rotacaoDuplaAEsq(NoAVL<T> *k3) {
		k3->esquerda = rotacaoSimplesEsq(k3->esquerda);
		return rotacaoSimplesDir(k3);
	}

	static NoAVL<T>* rotacaoDuplaADir(NoAVL<T> *k3) {
		k3->direita = rotacaoSimplesDir(k3->direita);
		return rotacaoSimplesEsq(k3);
	}

	static int fatorDeBalanceamento(NoAVL<T>* nodo) {
		if (!nodo) {
			return 0;
		}

		int altEsq = nodo->esquerda ? nodo->esquerda->altura : -1;
		int altDir = nodo->direita ? nodo->direita->altura : -1;

		return altEsq - altDir;
	}

 public:

};

#endif /* NO_AVL_HPP */
