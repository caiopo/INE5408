#ifndef EXCEPTIONS_HPP
#define EXCEPTIONS_HPP

#include <stdexcept>

class ErroPistaCheia : public std::runtime_error {
public:
    ErroPistaCheia() : std::runtime_error("") { }
};

#endif  // EXCEPTIONS_HPP