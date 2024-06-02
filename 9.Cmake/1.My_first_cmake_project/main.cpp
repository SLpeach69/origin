#include <iostream>
#include <string>

int main() {
    setlocale(LC_ALL, "Russian");

    std::string name;

    std::cout << "Введите имя: ";
    std::cin >> name;

    std::cout << "Здравствуйте, " << name << "!" << std::endl;

    return 0;
}
