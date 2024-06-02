#pragma once
#include "Figure.h"

class Triangle : public Figure {
protected:
    int a, b, c;
    int A, B, C;

public:
    Triangle(int side_a, int side_b, int side_c, int angle_A, int angle_B, int angle_C) : a(side_a), b(side_b), c(side_c), A(angle_A), B(angle_B), C(angle_C) {}
    void print_info() override;
};