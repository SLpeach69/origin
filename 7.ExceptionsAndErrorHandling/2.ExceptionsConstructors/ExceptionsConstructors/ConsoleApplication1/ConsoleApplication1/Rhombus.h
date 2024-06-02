#pragma once
#include "Parallelogram.h"

class Rhombus : public Parallelogram {
public:
    Rhombus(int side) : Parallelogram(side, side) {
        if (side <= 0) {
            throw GeometricException("������ �������� ������. �������: ������������ ������ ��� �����.");
        }
    }

    void print_info() override;
};