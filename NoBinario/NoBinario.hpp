
#ifndef NO_BINARIO_HPP
#define NO_BINARIO_HPP

#include <vector>

template <typename T>
class NoBinario {
 protected:
	T* dado;
	NoBinario<T>* esquerda;
	NoBinario<T>* direita;
	std::vector<NoBinario<T>*> elementos;  //!< Elementos acessados durante
											// o percurso realizado

 public:
	NoBinario<T>(const T& d) :
		dado(new T(d)),
		esquerda(nullptr),
		direita(nullptr) {}

	virtual ~NoBinario() {
		// delete dado;

		// if (esquerda != nullptr)
		// 	delete esquerda;

		// if (direita != nullptr)
		// 	delete direita;
	}

	T* getDado() {
		return dado;
	}

	std::vector<NoBinario<T>*> getElementos() {
		return elementos;
	}

	NoBinario<T>* getEsquerda() {
		return esquerda;
	}

	NoBinario<T>* getDireita() {
		return direita;
	}

	T* busca(const T& dado, NoBinario<T>* arv) {
		while (arv != nullptr)
			if (dado == *arv->getDado())
				return arv->getDado();
			else
				if (*arv->getDado() < dado)
					arv = arv->getDireita();
				else
					arv = arv->getEsquerda();

		throw std::runtime_error("não encontado");
	}

	NoBinario<T>* inserir(const T& dado, NoBinario<T>* arv) {
		if (dado < *arv->getDado())
			if (arv->getEsquerda() == nullptr)
				arv->esquerda = new NoBinario(dado);
			else
				arv->inserir(dado, arv->getEsquerda());
		else
			if (arv->getDireita() == nullptr)
				arv->direita = new NoBinario(dado);
			else
				arv->inserir(dado, arv->getDireita());

		return arv;
	}

	// NoBinario<T>* remover(NoBinario<T>* arv, const T& dado) {
	// 	if (arv == nullptr)
	// 		return arv;

	// 	if (dado < *arv->getDado()) {
	// 		arv->esquerda = remover(arv->getEsquerda(), dado);
	// 		return arv;
	// 	}

	// 	if (dado > *arv->getDado()) {
	// 		arv->direita = remover(arv->getDireita(), dado);
	// 		return arv;
	// 	}

	// 	if (arv->getDireita() != nullptr && arv->getDireita() != nullptr) {
	// 		auto tmp = minimo(arv->getDireita());
	// 		arv->dado = tmp->getDado();
	// 		arv->direita = remover(arv->getDireita(), *arv->getDado());
	// 		return arv;
	// 	}

	// 	if (arv->getDireita() != nullptr) {
	// 		return arv->getDireita();
	// 	}

	// 	if (arv->getEsquerda() != nullptr) {
	// 		return arv->getEsquerda();
	// 	}

	// 	// delete arv;
	// 	return nullptr;
	// }


	NoBinario<T>* remover(NoBinario<T>* arv, const T& dado) {
		if (arv == nullptr)
			return arv;
		else {
			if (dado < *arv->getDado()) {
				arv->esquerda = remover(arv->getEsquerda(), dado);
				return arv;
			} else {
				if (dado > *arv->getDado()) {
					arv->direita = remover(arv->getDireita(), dado);
					return arv;
				} else {
					if (arv->getDireita() != nullptr && arv->getDireita() != nullptr) {
						auto tmp = minimo(arv->getDireita());
						arv->dado = tmp->getDado();
						arv->direita = remover(arv->getDireita(), *arv->getDado());
						return arv;
					} else {
						if (arv->getDireita() != nullptr)
							return arv->getDireita();
						else {
							if (arv->getEsquerda() != nullptr)
								return arv->getEsquerda();
							else {
								delete arv;
								return nullptr;
							}
						}
					}
				}
			}
		}
	}

	NoBinario<T>* minimo(NoBinario<T>* nodo) {
		while (nodo->getEsquerda() != nullptr)
			nodo = nodo->getEsquerda();
		return nodo;
	}

	void preOrdem(NoBinario<T>* nodo) {
		if (nodo != nullptr) {
			elementos.push_back(nodo);
			preOrdem(nodo->getEsquerda());
			preOrdem(nodo->getDireita());
		}
	}

	void emOrdem(NoBinario<T>* nodo) {
		if (nodo != nullptr) {
			preOrdem(nodo->getEsquerda());
			elementos.push_back(nodo);
			preOrdem(nodo->getDireita());
		}
	}

	void posOrdem(NoBinario<T>* nodo) {
		if (nodo != nullptr) {
			preOrdem(nodo->getEsquerda());
			preOrdem(nodo->getDireita());
			elementos.push_back(nodo);
		}
	}

};

#endif /* NO_BINARIO_HPP */