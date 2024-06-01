#include <iostream>
#include <cmath>

class Figure {
protected:
    std::string figure;
    int sides;

public:
    Figure(std::string nameOffigure, int num_sides) : figure(nameOffigure), sides(num_sides) {}

    virtual void print_info() {
        std::cout << "Фигура:" << figure << std::endl;
        std::cout << "Количество сторон: " << sides << std::endl;
    }

    virtual bool is_valid() {
        return false;
    }
};

class Triangle : public Figure {
protected:
    int a, b, c;
    int A, B, C;

public:
    Triangle(std::string nameoffigure, int side_a, int side_b, int side_c, int angle_A, int angle_B, int angle_C) : Figure(nameoffigure, 3), a(side_a), b(side_b), c(side_c), A(angle_A), B(angle_B), C(angle_C) {}

    void print_info() override {
        Figure::print_info();
        std::cout << "Стороны: a=" << a << " b=" << b << " c=" << c << std::endl;
        std::cout << "Углы: A=" << A << " B=" << B << " C=" << C << std::endl;
    }

    bool is_valid() override {
        return (A + B + C == 180);
    }
};

class RightTriangle : public Triangle {
public:
    RightTriangle(std::string nameoffigure, int side_a, int side_b, int side_c) : Triangle(nameoffigure, side_a, side_b, side_c, 90, 45, 45) {}

    bool is_valid() override {
        return (Triangle::is_valid() && C == 90);
    }
};

class IsoscelesTriangle : public Triangle {
public:
    IsoscelesTriangle(std::string nameoffigure, int side_a, int side_b, int side_c) : Triangle(nameoffigure, side_a, side_b, side_c, 60, 60, 60) {}

    bool is_valid() override {
        return (Triangle::is_valid() && a == c && A == C);
    }
};

class EquilateralTriangle : public Triangle {
public:
    EquilateralTriangle(std::string nameoffigure, int side) : Triangle(nameoffigure, side, side, side, 60, 60, 60) {}

    bool is_valid() override {
        return (Triangle::is_valid() && a == b && b == c && A == B && B == C);
    }
};

class Quadrilateral : public Figure {
protected:
    int a, b, c, d;
    int A, B, C, D;

public:
    Quadrilateral(std::string nameoffigure, int side_a, int side_b, int side_c, int side_d, int angle_A, int angle_B, int angle_C, int angle_D)
        : Figure(nameoffigure, 4), a(side_a), b(side_b), c(side_c), d(side_d), A(angle_A), B(angle_B), C(angle_C), D(angle_D) {}

    void print_info() override {
        Figure::print_info();
        std::cout << "Стороны: a=" << a << " b=" << b << " c=" << c << " d=" << d << std::endl;
        std::cout << "Углы: A=" << A << " B=" << B << " C=" << C << " D=" << D << std::endl;
    }

    bool is_valid() override {
        return (A + B + C + D == 360);
    }
};

class Rectangle : public Quadrilateral {
public:
    Rectangle(std::string nameoffigure, int side_a, int side_b) : Quadrilateral(nameoffigure, side_a, side_b, side_a, side_b, 90, 90, 90, 90) {}

    bool is_valid() override {
        return (Quadrilateral::is_valid() && a == c && b == d);
    }
};

class Square : public Rectangle {
public:
    Square(std::string nameoffigure, int side) : Rectangle(nameoffigure, side, side) {}

    bool is_valid() override {
        return (Rectangle::is_valid() && a == b && b == c && c == d);
    }
};

class Parallelogram : public Quadrilateral {
public:
    Parallelogram(std::string nameoffigure, int side_a, int side_b) : Quadrilateral(nameoffigure, side_a, side_b, side_a, side_b, 30, 40, 30, 40) {}

    bool is_valid() override {
        return (Quadrilateral::is_valid() && a == c && b == d && A == C && B == D);
    }
};

class Rhombus : public Parallelogram {
public:
    Rhombus(std::string nameoffigure, int side) : Parallelogram(nameoffigure, side, side) {}

    bool is_valid() override {
        return (Parallelogram::is_valid() && a == b && b == c && c == d && A == B && B == C && C == D);
    }
};

int main() {
    setlocale(LC_ALL, "Russian");

    Figure figure("", 0);
    Triangle triangle("Треугольник", 10, 20, 30, 50, 60, 70);
    RightTriangle right_triangle("Прямоугольный треугольник", 10, 20, 30);
    IsoscelesTriangle isosceles_triangle("Равнобедренный треугольник", 10, 20, 10);
    EquilateralTriangle equilateral_triangle("Равносторонний треугольник", 30);

    Quadrilateral quadrilateral("Четырехугольник", 10, 20, 30, 40, 50, 60, 70, 80);
    Rectangle rectangle("Прямоугольник", 10, 20);
    Square square("Квадрат", 20);
    Parallelogram parallelogram("Параллелограмм", 20, 30);
    Rhombus rhombus("Ромб", 30);

    Figure* figures[] = {&figure, &triangle, &right_triangle, &isosceles_triangle,
                         &equilateral_triangle, &quadrilateral, &rectangle,
                         &square, &parallelogram, &rhombus };

    for (Figure* figure : figures) {
        if (figure->is_valid()) {
            std::cout << "Правильная" << std::endl;
        }
        else {
            std::cout << "Неправильная" << std::endl;
        }
        figure->print_info();
        std::cout << std::endl;
    }

    return 0;
}