#pragma once
#include "Triangle.h"

class EquilateralTriangle : public Triangle {
public:
    EquilateralTriangle(int side) : Triangle(side, side, side, 60, 60, 60) {
        if (side <= 0) {
            throw GeometricException("Ошибка создания фигуры. Причина: некорректные данные для Равностороннего треугольника.");
        }
    }

    void print_info() override;

};