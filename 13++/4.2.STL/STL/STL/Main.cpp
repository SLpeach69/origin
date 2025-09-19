#include <iostream>
#include <set>
#include <functional>

int main() {
    std::cout << "Enter the number of elements: ";
    int n;
    std::cin >> n;

    std::cout << "Enter " << n << " numbers :" << std::endl;

    std::set<int, std::greater<int>> unique_numbers;

    for (int i = 0; i < n; ++i) {
        int num;
        std::cin >> num;
        unique_numbers.insert(num);
    }

    std::cout << "\nResult :" << std::endl;

    for (int num : unique_numbers) {
        std::cout << num << std::endl;
    }

    return 0;
}