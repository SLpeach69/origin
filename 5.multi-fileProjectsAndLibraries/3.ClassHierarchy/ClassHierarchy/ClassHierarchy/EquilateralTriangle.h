#pragma once
#include "Triangle.h"

class EquilateralTriangle : public Triangle {
public:
    EquilateralTriangle(int side) : Triangle(side, side, side, 60, 60, 60) {}

    void print_info() override;

};