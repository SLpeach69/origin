#include "Exception.h"

const char* GeometricException::what() const noexcept {
    return message.c_str();
}