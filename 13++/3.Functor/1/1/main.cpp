#include <iostream>
#include <vector>
#include <type_traits>

template<typename T>
typename std::enable_if<std::is_arithmetic<T>::value, T>::type square(T x) {
    return x * x;
}

template<typename T>
std::vector<T> square(const std::vector<T>& vec) {
    std::vector<T> result;
    result.reserve(vec.size());
    for (const auto& element : vec) {
        result.push_back(element * element);
    }
    return result;
}

template<typename T>
void print_vector(const std::vector<T>& vec) {
    for (size_t i = 0; i < vec.size(); ++i) {
        std::cout << vec[i];
        if (i != vec.size() - 1) {
            std::cout << ", ";
        }
    }
    std::cout << std::endl;
}

int main() {
    std::cout << "Enter a number: ";
    int num;
    std::cin >> num;
    std::cout << "Result: " << square(num) << std::endl;

    std::cout << "\nEnter vector size: ";
    int size;
    std::cin >> size;

    std::cout << "Enter " << size << " numbers:" << std::endl;
    std::vector<int> vec(size);
    for (int i = 0; i < size; ++i) {
        std::cin >> vec[i];
    }

    std::vector<int> squared_vec = square(vec);
    std::cout << "Result: ";
    print_vector(squared_vec);

    return 0;
}