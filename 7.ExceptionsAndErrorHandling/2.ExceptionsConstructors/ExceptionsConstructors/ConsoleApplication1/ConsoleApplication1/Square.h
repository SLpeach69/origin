#pragma once
#include "Rectangle.h"

class Square : public Rectangle {
public:
    Square(int side) : Rectangle(side, side) {
        if (side <= 0) {
            throw GeometricException("Ошибка создания фигуры. Причина: некорректные данные для квадрата.");
        }
    }

    void print_info() override;
};