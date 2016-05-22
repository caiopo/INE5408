#ifndef EXCEPTIONS_HPP
#define EXCEPTIONS_HPP

#include <stdexcept>

class ErroPistaCheia : public std::runtime_error {
public:
    ErroPistaCheia() : std::runtime_error("") { }
};

class SemaforoNaoEstaNaDirecao : public std::runtime_error {
public:
    SemaforoNaoEstaNaDirecao() : std::runtime_error("") { }
};


#endif  // EXCEPTIONS_HPP