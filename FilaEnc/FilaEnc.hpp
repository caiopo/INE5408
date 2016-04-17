#ifndef FILAENC_HPP
#define FILAENC_HPP

#include <memory>
#include <stdexcept>
#include "Elemento.hpp"


template <typename T>
class FilaEnc {
 private:
	std::shared_ptr<Elemento<T>> tail = nullptr;
	std::shared_ptr<Elemento<T>> head = nullptr;

 public:
	FilaEnc() = default;

	~FilaEnc() {
		head = nullptr;
		tail = nullptr;
	}

	void inclui(const T& dado) {
		if(filaVazia()) {
			head = std::make_shared<Elemento<T>>(dado, nullptr);
			tail = head;
		} else {
			tail->setProximo(std::make_shared<Elemento<T>>(dado, nullptr));
			tail = tail->getProximo();
		}
	}

	T retira() {
		if(filaVazia())
			throw std::runtime_error("fila vazia");

		T retirado = head->getInfo();
		head = head->getProximo();

		return retirado;

	}

	T ultimo() {
		if(filaVazia())
			throw std::runtime_error("fila vazia");
		return tail->getInfo();
	}

	T primeiro() {
		if(filaVazia())
			throw std::runtime_error("fila vazia");

		return head->getInfo();
	}

	bool filaVazia() {
		return head == nullptr;
	}

	void limparFila() {
		head = nullptr;
		tail = nullptr;
	}
};

#endif  // FILAENC_HPP