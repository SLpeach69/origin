#include <iostream>

class calculator
{
public:
    
    calculator() : num1(0), num2(0) {}

    double add()
    {
        return num1 + num2;
    }

    double multiply()
    {
        return num1 * num2;
    }

    double subtract_2_1()
    {
        return num2 - num1;
    }

    double subtract_1_2()
    {
        return num1 - num2;
    }
    
    double divide_1_2()
    {
        return num1 / num2;
    }

    double divide_2_1()
    {
        return num2 / num1;
    }

    bool set_num1(double num1)
    {
        if (num1 == 0)
        {
            return 0;
        }
        else {
            this->num1 = num1;
            return 1;
        }
    }

    bool set_num2(double num2)
    {
        if (num2 == 0)
        {
            return 0;
        }
        else {
            this->num2 = num2;
            return 1;
        }
    }

private:
    double num1;
    double num2;
};

int main()
{
    setlocale(LC_ALL, "Russian");

    double x1 = 0, x2 = 0;
    calculator calc;
    while (true)
    {
        std::cout << "Введите num1: ";
        std::cin >> x1;
        if (!calc.set_num1(x1)) {
            std::cout << "Неверный ввод! num1 не должен быть равен 0." << std::endl;
            continue;
        }

        std::cout << "Введите num2: ";
        std::cin >> x2;
        bool set_num2(double x2);
        if (!calc.set_num2(x2)) {
            std::cout << "Неверный ввод! num2 не должен быть равен 0." << std::endl;
            continue;
        }

        std::cout << x1 << " + " << x2 << " = " << calc.add() << std::endl;
        std::cout << x1 << " * " << x2 << " = " << calc.multiply() << std::endl;
        std::cout << x1 << " - " << x2 << " = " << calc.subtract_1_2() << std::endl;
        std::cout << x2 << " - " << x1 << " = " << calc.subtract_2_1() << std::endl;
        std::cout << x1 << " / " << x2 << " = " << calc.divide_1_2() << std::endl;
        std::cout << x2 << " / " << x1 << " = " << calc.divide_2_1() << std::endl;
    }

    return 0;
    
}

/*double add() - метод должен возвращать результат сложения num1 и num2
double multiply() - метод должен возвращать результат перемножения num1 и num2
double subtract_1_2() - метод должен возвращать результат вычитания num2 из num1
double subtract_2_1() - метод должен возвращать результат вычитания num1 из num2
double divide_1_2() - метод должен возвращать результат деления num1 на num2
double divide_2_1() - метод должен возвращать результат деления num2 на num1
bool set_num1(double num1) - метод должен установить значение поля num1 равное значению аргумента num1 в случае, если значение аргумента не равно 0. Возвращает true, если установка произошла успешно, в обратном случае false
bool set_num2(double num2) - метод должен установить значение поля num2 равное значению аргумента num2 в случае, если значение аргумента не равно 0. Возвращает true, если установка произошла успешно, в обратном случае false
*/