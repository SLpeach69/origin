#include "counter.h"
#include <iostream>

counter::counter(int initNum) : num(initNum) {}

int counter::add()
{
    return num++;
}

int counter::minus()
{
    return num--;
}

void counter::printNum()
{
    std::cout << num << std::endl;
}