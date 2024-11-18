#ifndef ILLEGAL_EXCEPTION_H
#define ILLEGAL_EXCEPTION_H

#include <exception>

class IllegalException : public std::exception {
   public:
    const char* what() const noexcept override;
};

#endif
