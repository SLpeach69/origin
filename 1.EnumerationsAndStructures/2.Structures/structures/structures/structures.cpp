#include <iostream>
#include <string>

struct bankID 
{
    int ID;
    std::string firstName;
    float balance;
};

void swap(float* a, float* b) {
    float swp = *a;
    *a = *b;
    *b = swp;
}

int main()
{
    setlocale(LC_ALL, "rus");

    int id = 0;
    std::string FirstName = "Ivan";
    float balance = 0;
    float newBalance = 0;

    std::cout << "Введите информацию о счёте" << std::endl;
    std::cout << "Введите номер счёта" << std::endl;
    std::cin >> id;
    std::cout << "Введите имя" << std::endl;
    std::cin >> FirstName;
    std::cout << "Введите баланс" << std::endl;
    std::cin >> balance;
    std::cout << "Введите новый баланс" << std::endl;
    std::cin >> newBalance;

    swap(&balance, &newBalance);

    bankID checkInfo;
    checkInfo.ID = id;
    checkInfo.firstName = FirstName;
    checkInfo.balance = balance;

    std::cout << "Ваш счёт: " << checkInfo.ID << ", " << checkInfo.firstName << ", " << checkInfo.balance << std::endl;
  
    return 0;
}

