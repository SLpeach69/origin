#pragma once
#include "Quadrilateral.h"

class Rectangle : public Quadrilateral {
public:
    Rectangle(int side_a, int side_b) : Quadrilateral(side_a, side_b, side_a, side_b, 90, 90, 90, 90) {
        if (side_a <= 0 || side_b <= 0 ) {
            throw GeometricException("Ошибка создания фигуры. Причина: некорректные данные для прямоугольника.");
        }
    }

    void print_info() override;
};
