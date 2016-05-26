#ifndef EXCEPTIONS_HPP
#define EXCEPTIONS_HPP

#include <stdexcept>

/**
 * @brief      Representa a exception jogada quando um carro tenta trocar de pista e o semáforo não está na direcão
 */
class SemaforoNaoEstaNaDirecao : public std::runtime_error {
public:
    SemaforoNaoEstaNaDirecao() : std::runtime_error("") { }
};


#endif  // EXCEPTIONS_HPP