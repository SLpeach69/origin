#pragma once

class counter
{
public:
    counter(int initNum = 1);

    int add();
    int minus();
    void printNum();

private:
    int num;
};