#ifndef PILHAENC_HPP
#define PILHAENC_HPP

#include <memory>
#include <stdexcept>
#include "Elemento.hpp"

template<typename T>
class PilhaEnc{
 private:
    std::shared_ptr<Elemento<T>> head = nullptr;

 public:
    PilhaEnc() = default;

    ~PilhaEnc() {
        head = nullptr;
    }

    void empilha(const T& dado) {
        head = std::make_shared<Elemento<T>>(dado, head);
    }

    T desempilha() {
        if(PilhaVazia())
            throw std::runtime_error("fila vazia");

        T removido = head->getInfo();
        head = head->getProximo();
        return removido;
    }

	T topo() {
        if(PilhaVazia())
            throw std::runtime_error("fila vazia");

        return head->getInfo();
	}

	void limparPilha() {
        head = nullptr;
	}

	bool PilhaVazia() {
        return head == nullptr;
	}
};

#endif  // PILHAENC_HPP
