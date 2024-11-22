#include "IllegalException.h"

const char* IllegalException::what() const noexcept {
    return "illegal argument";
}
