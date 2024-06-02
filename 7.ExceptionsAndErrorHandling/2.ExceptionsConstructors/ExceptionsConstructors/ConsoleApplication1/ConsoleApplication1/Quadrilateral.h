#pragma once
#include "Figure.h"

class Quadrilateral : public Figure {
protected:
    int a, b, c, d;
    int A, B, C, D;

public:
    Quadrilateral(int side_a, int side_b, int side_c, int side_d, int angle_A, int angle_B, int angle_C, int angle_D)
        : a(side_a), b(side_b), c(side_c), d(side_d), A(angle_A), B(angle_B), C(angle_C), D(angle_D) {
        if (side_a <= 0 || side_b <= 0 || side_c <= 0 || side_d <= 0 || angle_A <= 0 || angle_B <= 0 || angle_C <= 0 || angle_D <= 0 || angle_A + angle_B + angle_C + angle_D != 360) {
            throw GeometricException("Ошибка создания фигуры. Причина: некорректные данные для четырёхугольника.");
        }
    }

    void print_info() override;
};