#pragma once
#include <iostream>
#include "Exception.h"

class Figure {
protected:
    Figure() {}

public:
    virtual void print_info() = 0;
};