#pragma once
#include "Triangle.h"
class RightTriangle : public Triangle {
public:
    RightTriangle(int side_a, int side_b, int side_c) : Triangle(side_a, side_b, side_c, 90, 45, 45) {}

    void print_info() override;
};