#include <iostream>
#include <string>

struct address
{
    std::string city;
    std::string street;
    int house;
    int apartment;
    int index;
};

void printAddress(const address& adr) {
    std::cout << "Город: " << adr.city << std::endl;
    std::cout << "Улица: " << adr.street << std::endl;
    std::cout << "Дом: " << adr.house << std::endl;
    std::cout << "Квартира: " << adr.apartment << std::endl;
    std::cout << "Индекс: " << adr.index << std::endl << std::endl;
}

int main()
{
    setlocale(LC_ALL, "rus");

    address address1, address2;

    address1.city = "Moscow";
    address1.street = "Tverskaya";
    address1.house = 1;
    address1.apartment = 1;
    address1.index = 1234567;

    printAddress(address1);

    address2.city = "Tver";
    address2.street = "Moscowskaya";
    address2.house = 2;
    address2.apartment = 2;
    address2.index = 7654321;

    printAddress(address2);


    return 0;
}
