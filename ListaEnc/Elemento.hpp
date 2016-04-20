#ifndef ELEMENTO_HPP
#define ELEMENTO_HPP

#include <memory>

template<typename T>
class Elemento {
private:
	T *info;
	std::shared_ptr<Elemento<T>> _next;

public:
	Elemento(const T& _info, std::shared_ptr<Elemento<T>> next) : info(new T(_info)), _next(next) {}

	~Elemento() {
		delete info;
	}

	std::shared_ptr<Elemento<T>> getProximo() const {
		return _next;
	}

	T getInfo() const {
		return *info;
	}

	void setProximo(std::shared_ptr<Elemento<T>> next) {
		_next = next;
	}
};

#endif
