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
#include "Exception.h"


int main() {
    setlocale(LC_ALL, "Russian");


    try {
        Triangle triangle(10, 20, 30, 50, 60, 70);
        RightTriangle right_triangle(10, 20, 30);
        IsoscelesTriangle isosceles_triangle(10, 20, 10);
        EquilateralTriangle equilateral_triangle(30);

        Quadrilateral quadrilateral(10, 20, 30, 40, 75, 85, 95, 105);
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
    }
    catch (const GeometricException& ex) {
        std::cout << "Произошла ошибка: " << ex.what() << std::endl;

        return 0;
    }
}
