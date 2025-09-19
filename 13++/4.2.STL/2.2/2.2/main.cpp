#include <iostream>
#include <set>
#include <vector>
#include <list>
#include <string>

template<typename Container>
void print_container(const Container& container) {
    auto it = container.begin();
    if (it == container.end()) {
        std::cout << "{}";
        return;
    }

    std::cout << *it;
    ++it;

    for (; it != container.end(); ++it) {
        std::cout << ", " << *it;
    }
}

int main() {
    std::set<std::string> test_set = { "one", "two", "three", "four" };
    std::cout << "Set: ";
    print_container(test_set);
    std::cout << std::endl;

    std::list<std::string> test_list = { "one", "two", "three", "four" };
    std::cout << "List: ";
    print_container(test_list);
    std::cout << std::endl;

    std::vector<std::string> test_vector = { "one", "two", "three", "four" };
    std::cout << "Vector: ";
    print_container(test_vector);
    std::cout << std::endl;

    return 0;
}