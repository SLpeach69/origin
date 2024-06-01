#include <iostream>
#include <string>

class Figure {
protected:
    int sides_count;
    std::string name;

public:
    Figure(int sides = 0, std::string figure_name = "Figure") : sides_count(sides), name(figure_name) {}

    int get_sides_count() {
        return sides_count;
    }

    std::string get_name() {
        return name;
    }
};

class Triangle : public Figure {
public:
    Triangle() : Figure(3, "Triangle") {}
};

class Quadrangle : public Figure {
public:
    Quadrangle() : Figure(4, "Quadrangle") {}
};

int main() {
    Figure figure;
    Triangle triangle;
    Quadrangle quadrangle;

    std::cout << "Number of sides:" << std::endl;
    std::cout << figure.get_name() << ": " << figure.get_sides_count() << std::endl;
    std::cout << triangle.get_name() << ": " << triangle.get_sides_count() << std::endl;
    std::cout << quadrangle.get_name() << ": " << quadrangle.get_sides_count() << std::endl;

    return 0;
}