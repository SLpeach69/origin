#include <iostream>
#include <fstream>
#include <string>

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
};

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

    outputFile << n << std::endl;

    for (int i = n - 1; i >= 0; --i) {
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
