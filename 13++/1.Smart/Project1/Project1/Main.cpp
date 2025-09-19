#include <iostream>
#include <stdexcept>
#include <algorithm> 

class smart_array {
private:
    int* data;
    size_t size;
    size_t capacity;

    void resize() {
        capacity *= 2;
        int* new_data = new int[capacity];
        std::copy(data, data + size, new_data);
        delete[] data;
        data = new_data;
    }

public:
    explicit smart_array(size_t initial_capacity)
        : size(0), capacity(initial_capacity) {
        if (initial_capacity == 0) {
            throw std::invalid_argument("Capacity cannot be zero");
        }
        data = new int[capacity];
    }

    void add_element(int element) {
        if (size >= capacity) {
            resize();
        }
        data[size] = element;
        size++;
    }

    int get_element(size_t index) const {
        if (index >= size) {
            throw std::out_of_range("Index out of range");
        }
        return data[index];
    }

    ~smart_array() {
        delete[] data;
    }

    smart_array(const smart_array&) = delete;
    smart_array& operator=(const smart_array&) = delete;
};

int main() {
    try {
        smart_array arr(5);
        arr.add_element(1);
        arr.add_element(4);
        arr.add_element(155);
        arr.add_element(14);
        arr.add_element(15);
        std::cout << arr.get_element(1) << std::endl;
    }
    catch (const std::exception& ex) {
        std::cout << ex.what() << std::endl;
    }

    return 0;
}