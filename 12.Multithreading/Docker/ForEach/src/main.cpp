#include <iostream>
#include <vector>
#include <future>
#include <algorithm>

template<typename Iterator, typename Func>
void parallel_for_each(Iterator first, Iterator last, Func f) {
    size_t length = std::distance(first, last);

    if (length <= 1) {
        std::for_each(first, last, f);
        return;
    }

    Iterator middle = first;
    std::advance(middle, length / 2);

    auto future = std::async(std::launch::async, parallel_for_each<Iterator, Func>, middle, last, f);
    parallel_for_each(first, middle, f);

    future.get();
}

void print_square(int& x) {
    x = x * x;
}

int main() {
    std::vector<int> data = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

    std::cout << "Before: ";
    for (int x : data) {
        std::cout << x << " ";
    }
    std::cout << std::endl;

    parallel_for_each(data.begin(), data.end(), print_square);

    std::cout << "After: ";
    for (int x : data) {
        std::cout << x << " ";
    }
    std::cout << std::endl;

    return 0;
}