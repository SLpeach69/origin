#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>

template<typename T>
void remove_duplicates(std::vector<T>& vec) {
    std::sort(vec.begin(), vec.end());

    auto last = std::unique(vec.begin(), vec.end());

    vec.erase(last, vec.end());
}

int main() {
    std::vector<int> vec = { 1, 1, 2, 5, 6, 1, 2, 4 };

    std::cout << "Input: ";
    for (int num : vec) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    remove_duplicates(vec);

    std::cout << "Output: ";
    for (int num : vec) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    return 0;
}