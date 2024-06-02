#pragma once
#include "Quadrilateral.h"

class Parallelogram : public Quadrilateral {
public:
    Parallelogram(int side_a, int side_b) : Quadrilateral(side_a, side_b, side_a, side_b, 30, 40, 30, 40) {}

    void print_info() override;
};