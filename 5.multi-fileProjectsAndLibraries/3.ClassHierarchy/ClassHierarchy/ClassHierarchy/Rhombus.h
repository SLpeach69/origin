#pragma once
#include "Parallelogram.h"

class Rhombus : public Parallelogram {
public:
    Rhombus(int side) : Parallelogram(side, side) {}

    void print_info() override;
};