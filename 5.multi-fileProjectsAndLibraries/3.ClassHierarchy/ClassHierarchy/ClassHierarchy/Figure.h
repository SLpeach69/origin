#pragma once
#include <iostream>

class Figure {
protected:
    Figure() {}

public:
    virtual void print_info() = 0;
};