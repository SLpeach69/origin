#pragma once
#include <exception>
#include <string>

class GeometricException : public std::exception {
private:
    std::string message;

public:
    GeometricException(const std::string& msg) : message(msg) {}
    const char* what() const noexcept override;
};