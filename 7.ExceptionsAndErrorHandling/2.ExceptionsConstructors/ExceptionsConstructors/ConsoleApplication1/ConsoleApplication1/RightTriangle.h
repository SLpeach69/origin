#pragma once
#include "Triangle.h"
class RightTriangle : public Triangle {
public:
    RightTriangle(int side_a, int side_b, int side_c) : Triangle(side_a, side_b, side_c, 90, 45, 45) {
        if ((side_a <= 0) || (side_b <= 0) || (side_c <= 0)) {
            throw GeometricException("Ошибка создания фигуры. Причина: некорректные данные для Прямоугольного треугольника.");
        }
    }
    void print_info() override;
};