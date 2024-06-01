#pragma once
#include "Rectangle.h"

class Square : public Rectangle {
public:
    Square(int side) : Rectangle(side, side) {}

    void print_info() override;
};