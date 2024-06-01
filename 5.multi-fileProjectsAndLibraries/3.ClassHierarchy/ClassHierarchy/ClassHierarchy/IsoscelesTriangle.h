#pragma once
#include "Triangle.h"
class IsoscelesTriangle : public Triangle {
public:
    IsoscelesTriangle(int side_a, int side_b, int side_c) : Triangle(side_a, side_b, side_c, 60, 60, 60) {}
    void print_info() override;
};