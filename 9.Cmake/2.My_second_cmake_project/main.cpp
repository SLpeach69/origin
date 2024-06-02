#include <iostream>
#include "Figure.h"
#include "EquilateralTriangle.h"
#include "IsoscelesTriangle.h"
#include "Parallelogram.h"
#include "Quadrilateral.h"
#include "Rectangle.h"
#include "Rhombus.h"
#include "RightTriangle.h"
#include "Square.h"
#include "Triangle.h"

/*class Figure {
protected:
    Figure() {}

public:
    virtual void print_info() = 0;
};

class Triangle : public Figure {
protected:
    int a, b, c;
    int A, B, C;

public:
    Triangle(int side_a, int side_b, int side_c, int angle_A, int angle_B, int angle_C) : a(side_a), b(side_b), c(side_c), A(angle_A), B(angle_B), C(angle_C) {}

    void print_info() override {
        std::cout << "�����������:" << std::endl;
        std::cout << "�������: a=" << a << " b=" << b << " c=" << c << std::endl;
        std::cout << "����: A=" << A << " B=" << B << " C=" << C << std::endl;
    }
};

class RightTriangle : public Triangle {
public:
    RightTriangle(int side_a, int side_b, int side_c) : Triangle(side_a, side_b, side_c, 90, 45, 45) {}

    void print_info() override {
        std::cout << "������������� �����������:" << std::endl;
        std::cout << "�������: a=" << a << " b=" << b << " c=" << c << std::endl;
        std::cout << "����: A=" << A << " B=" << B << " C=" << C << std::endl;
    }
};

class IsoscelesTriangle : public Triangle {
public:
    IsoscelesTriangle(int side_a, int side_b, int side_c) : Triangle(side_a, side_b, side_c, 60, 60, 60) {}

    void print_info() override {
        std::cout << "�������������� �����������:" << std::endl;
        std::cout << "�������: a=" << a << " b=" << b << " c=" << c << std::endl;
        std::cout << "����: A=" << A << " B=" << B << " C=" << C << std::endl;
    }
};

class EquilateralTriangle : public Triangle {
public:
    EquilateralTriangle(int side) : Triangle(side, side, side, 60, 60, 60) {}

    void print_info() override {
        std::cout << "�������������� �����������:" << std::endl;
        std::cout << "�������: a=" << a << " b=" << b << " c=" << c << std::endl;
        std::cout << "����: A=" << A << " B=" << B << " C=" << C << std::endl;
    }
};

class Quadrilateral : public Figure {
protected:
    int a, b, c, d;
    int A, B, C, D;

public:
    Quadrilateral(int side_a, int side_b, int side_c, int side_d, int angle_A, int angle_B, int angle_C, int angle_D)
        : a(side_a), b(side_b), c(side_c), d(side_d), A(angle_A), B(angle_B), C(angle_C), D(angle_D) {}

    void print_info() override {
        std::cout << "��������������:" << std::endl;
        std::cout << "�������: a=" << a << " b=" << b << " c=" << c << " d=" << d << std::endl;
        std::cout << "����: A=" << A << " B=" << B << " C=" << C << " D=" << D << std::endl;
    }
};

class Rectangle : public Quadrilateral {
public:
    Rectangle(int side_a, int side_b) : Quadrilateral(side_a, side_b, side_a, side_b, 90, 90, 90, 90) {}

    void print_info() override {
        std::cout << "�������������:" << std::endl;
        std::cout << "�������: a=" << a << " b=" << b << " c=" << c << " d=" << d << std::endl;
        std::cout << "����: A=" << A << " B=" << B << " C=" << C << " D=" << D << std::endl;
    }
};

class Square : public Rectangle {
public:
    Square(int side) : Rectangle(side, side) {}

    void print_info() override {
        std::cout << "�������:" << std::endl;
        std::cout << "�������: a=" << a << std::endl;
        std::cout << "����: A=" << A << " B=" << B << " C=" << C << " D=" << D << std::endl;
    }
};

class Parallelogram : public Quadrilateral {
public:
    Parallelogram(int side_a, int side_b) : Quadrilateral(side_a, side_b, side_a, side_b, 30, 40, 30, 40) {}

    void print_info() override {
        std::cout << "��������������:" << std::endl;
        std::cout << "�������: a=" << a << " b=" << b << " c=" << c << " d=" << d << std::endl;
        std::cout << "����: A=" << A << " B=" << B << " C=" << C << " D=" << D << std::endl;
    }
};

class Rhombus : public Parallelogram {
public:
    Rhombus(int side) : Parallelogram(side, side) {}

    void print_info() override {
        std::cout << "����:" << std::endl;
        std::cout << "�������: a=" << a << std::endl;
        std::cout << "����: A=" << A << " B=" << B << " C=" << C << " D=" << D << std::endl;
    }
};
*/

int main() {
    setlocale(LC_ALL, "Russian");

    Triangle triangle(10, 20, 30, 50, 60, 70);
    RightTriangle right_triangle(10, 20, 30);
    IsoscelesTriangle isosceles_triangle(10, 20, 10);
    EquilateralTriangle equilateral_triangle(30);

    Quadrilateral quadrilateral(10, 20, 30, 40, 50, 60, 70, 80);
    Rectangle rectangle(10, 20);
    Square square(20);
    Parallelogram parallelogram(20, 30);
    Rhombus rhombus(30);

    triangle.print_info();
    right_triangle.print_info();
    isosceles_triangle.print_info();
    equilateral_triangle.print_info();

    quadrilateral.print_info();
    rectangle.print_info();
    square.print_info();
    parallelogram.print_info();
    rhombus.print_info();

    return 0;
}
