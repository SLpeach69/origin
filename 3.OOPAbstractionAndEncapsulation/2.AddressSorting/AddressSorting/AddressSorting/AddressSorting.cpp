#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

class Address {
private:
    std::string city;
    std::string street;
    int houseNumber;
    int appartment;

public:
    Address(std::string city, std::string street, int houseNumber, int appartment) : city(city), street(street), houseNumber(houseNumber), appartment(appartment) {}

    std::string OutputAddress() {
        return city + ", " + street + ", " + std::to_string(houseNumber) + ", " + std::to_string(appartment);
    }

    const std::string& getCity() const {
        return city;
    }

    
};

bool sortingCity(const Address* a, const Address* b) {
    return a->getCity() < b->getCity();
}

int main() {
    std::ifstream inputFile("in.txt");
    std::ofstream outputFile("out.txt");

    int n;
    inputFile >> n;

    Address** addresses = new Address * [n];

    for (int i = 0; i < n; ++i) {
        std::string city, street;
        int houseNumber, appartment;

        inputFile >> city >> street >> houseNumber >> appartment;

        addresses[i] = new Address(city, street, houseNumber, appartment);
    }


    std::sort(addresses, addresses + n, sortingCity);
    for (int i = 0; i < n; ++i) {
        outputFile << addresses[i]->OutputAddress() << std::endl;
    }

    for (int i = 0; i < n; ++i) {
        delete addresses[i];
    }
    delete[] addresses;

    inputFile.close();
    outputFile.close();

    return 0;
}