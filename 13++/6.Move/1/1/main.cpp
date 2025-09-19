#include <iostream>
#include <vector>
#include <string>
#include <utility> 

template<typename T>
void move_vectors(std::vector<T>& source, std::vector<T>& destination) {
    destination = std::move(source);
}

int main() {
    std::vector<std::string> one = { "test_string1", "test_string2" };
    std::vector<std::string> two;

    std::cout << "Before move:" << std::endl;
    std::cout << "one size: " << one.size() << ", capacity: " << one.capacity() << std::endl;
    std::cout << "two size: " << two.size() << ", capacity: " << two.capacity() << std::endl;

    move_vectors(one, two);

    std::cout << "\nAfter move:" << std::endl;
    std::cout << "one size: " << one.size() << ", capacity: " << one.capacity() << std::endl;
    std::cout << "two size: " << two.size() << ", capacity: " << two.capacity() << std::endl;

    std::cout << "\nContents of two:" << std::endl;
    for (const auto& str : two) {
        std::cout << str << std::endl;
    }

    return 0;
}