#include <iostream>
#include <mutex>
#include <thread>

class Data {
private:
    int value;
    mutable std::mutex mtx;

public:
    Data(int val = 0) : value(val) {}

    friend void swap_using_lock(Data& a, Data& b);
    friend void swap_using_scoped_lock(Data& a, Data& b);
    friend void swap_using_unique_lock(Data& a, Data& b);

    void print(const std::string& name) const {
        std::lock_guard<std::mutex> lock(mtx);
        std::cout << name << ": " << value << std::endl;
    }
};

void swap_using_lock(Data& a, Data& b) {
    std::lock(a.mtx, b.mtx);
    std::lock_guard<std::mutex> lock_a(a.mtx, std::adopt_lock);
    std::lock_guard<std::mutex> lock_b(b.mtx, std::adopt_lock);
    std::swap(a.value, b.value);
}

void swap_using_scoped_lock(Data& a, Data& b) {
    std::scoped_lock lock(a.mtx, b.mtx);
    std::swap(a.value, b.value);
}

void swap_using_unique_lock(Data& a, Data& b) {
    std::unique_lock<std::mutex> lock_a(a.mtx, std::defer_lock);
    std::unique_lock<std::mutex> lock_b(b.mtx, std::defer_lock);
    std::lock(lock_a, lock_b);
    std::swap(a.value, b.value);
}

void test_swap(void (*swap_func)(Data&, Data&), const std::string& name) {
    std::cout << "\n=== Testing " << name << " ===" << std::endl;

    Data data1(100);
    Data data2(200);

    std::cout << "Before swap:" << std::endl;
    data1.print("data1");
    data2.print("data2");

    swap_func(data1, data2);

    std::cout << "After swap:" << std::endl;
    data1.print("data1");
    data2.print("data2");
}

int main() {
    test_swap(swap_using_lock, "std::lock");
    test_swap(swap_using_scoped_lock, "std::scoped_lock");
    test_swap(swap_using_unique_lock, "std::unique_lock");

    return 0;
}