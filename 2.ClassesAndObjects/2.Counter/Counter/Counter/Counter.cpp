#include <iostream>
#include <string>

class counter
{
public:
    counter(int initNum = 1) : num(initNum) {}

    int add()
    {
        return num++;
    }

    int minus()
    {
        return num--;
    }

    void printNum()
    {
        std::cout << num << std::endl;
    }



private:
    int num;

};

int main()
{
    setlocale(LC_ALL, "Russian");

    char userCommand = 'f';
    int initNum = 1;

    std::string userInit;
    std::cout << "Вы хотите указать начальное значение счётчика? Введите yes или no " << std::endl;
   
    std::cin >> userInit;

    if (userInit == "yes")
    {
        std::cout << "Введите начальное значение: " << std::endl;
        std::cin >> initNum;
    }
    else if (userInit == "no")
    {
        std::cout << "Выбрано значение по умолчаню равное 1: " << std::endl;
    }
    else
    {
        std::cout << "Некорректный выбор. Используется число по умолчанию." << std::endl;
    }
    

    counter counter(initNum);

    while (userCommand != 'x')
    {
        std::cout << "Введите команду +, -, =, или x для выхода: " << std::endl;
        std::cin >> userCommand;
        switch (userCommand)
        {
        case '+': counter.add(); break;
        case '-': counter.minus(); break;
        case '=': counter.printNum(); break;
        case 'x': std::cout << "До свидания!" << std::endl; break;
        default: std::cout << "Некорректная команда. Попробуйте еще раз." << std::endl;
        }
    } 
    return 0;
}

