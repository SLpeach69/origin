#include <iostream>
#include <cmath>
#include "math.h"

/*double add(double a, double b) {
    return a + b;
}

double subtract(double a, double b) {
    return a - b;
}

double multiply(double a, double b) {
    return a * b;
}

double divide(double a, double b) {
    if (b != 0) {
        return a / b;
    }
    else {
        std::cout << "Ошибка: деление на ноль" << std::endl;
        return 0;
    }
}

double power(double base, double exponent) {
    return pow(base, exponent);
}

*/

int main() {
    setlocale(LC_ALL, "Russian");

    double num1, num2;
    int operation;

    std::cout << "Введите первое число: ";
    std::cin >> num1;

    std::cout << "Введите второе число: ";
    std::cin >> num2;

    std::cout << "Выберите операцию (1 - сложение, 2 - вычитание, 3 - умножение, 4 - деление, 5 - возведение в степень): ";
    std::cin >> operation;

    switch (operation) {
    case 1:
        std::cout << "Результат сложения: " << add(num1, num2) << std::endl;
        break;
    case 2:
        std::cout << "Результат вычитания: " << subtract(num1, num2) << std::endl;
        break;
    case 3:
        std::cout << "Результат умножения: " << multiply(num1, num2) << std::endl;
        break;
    case 4:
        std::cout << "Результат деления: " << divide(num1, num2) << std::endl;
        break;
    case 5:
        std::cout << num1 << " в степени " << num2 << " = " << power(num1, num2) << std::endl;
        break;
    default:
        std::cout << "Ошибка: Некорректная операция" << std::endl;
    }

    return 0;
}