// Copyright 2016 Caio Pereira Oliveira

#ifndef ELEMENTO_HPP
#define ELEMENTO_HPP

#include <memory>

template<typename T>
class Elemento {
 private:
	T *info;
	std::shared_ptr<Elemento<T>> _prev;
	std::shared_ptr<Elemento<T>> _next;

 public:
	Elemento(const T& _info,
			std::shared_ptr<Elemento<T>> prev,
			std::shared_ptr<Elemento<T>> next)
			: info(new T(_info)), _prev(prev), _next(next) {}

	~Elemento() {
		delete info;
	}

	T getInfo() const {
		return *info;
	}

	std::shared_ptr<Elemento<T>> getProximo() const {
		return _next;
	}

	void setProximo(std::shared_ptr<Elemento<T>> next) {
		_next = next;
	}

	std::shared_ptr<Elemento<T>> getAnterior() const {
		return _prev;
	}

	void setAnterior(std::shared_ptr<Elemento<T>> prev) {
		_prev = prev;
	}
};

#endif
