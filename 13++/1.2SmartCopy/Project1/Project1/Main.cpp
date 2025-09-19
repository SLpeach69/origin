#include <iostream>
#include <stdexcept>
#include <algorithm> 

class SmartArray {
private:
    int* data;
    size_t currentSize;
    size_t currentCapacity;

    void resize() {
        currentCapacity *= 2;
        int* newData = new int[currentCapacity];

        for (size_t i = 0; i < currentSize; ++i) {
            newData[i] = data[i];
        }

        delete[] data;
        data = newData;
    }

    
    void cleanup() {
        delete[] data;
        data = nullptr;
        currentSize = 0;
        currentCapacity = 0;
    }

    
    void copyFrom(const SmartArray& other) {
        currentSize = other.currentSize;
        currentCapacity = other.currentCapacity;
        data = new int[currentCapacity];

        
        for (size_t i = 0; i < currentSize; ++i) {
            data[i] = other.data[i];
        }
    }

public:
    SmartArray(size_t initialCapacity = 10)
        : currentSize(0), currentCapacity(initialCapacity) {
        if (initialCapacity == 0) {
            throw std::invalid_argument("Capacity cannot be zero");
        }
        data = new int[currentCapacity];
    }

    
    SmartArray(const SmartArray& other) {
        copyFrom(other);
    }

    
    SmartArray& operator=(const SmartArray& other) {
        if (this != &other) { 
            cleanup();        
            copyFrom(other);  
        }
        return *this;
    }

    void addElement(int element) {
        if (currentSize >= currentCapacity) {
            resize();
        }
        data[currentSize] = element;
        currentSize++;
    }

    int getElement(size_t index) const {
        if (index >= currentSize) {
            throw std::out_of_range("Index out of range");
        }
        return data[index];
    }

    size_t getSize() const {
        return currentSize;
    }

    size_t getCapacity() const {
        return currentCapacity;
    }

    ~SmartArray() {
        cleanup();
    }
};


void testCopying() {
    try {
        std::cout << "Testing SmartArray copying \n";

        
        SmartArray arr1(5);
        arr1.addElement(1);
        arr1.addElement(4);
        arr1.addElement(155);

        std::cout << "arr1 size: " << arr1.getSize() << std::endl;
        std::cout << "arr1 elements: ";
        for (size_t i = 0; i < arr1.getSize(); ++i) {
            std::cout << arr1.getElement(i) << " ";
        }
        std::cout << std::endl;

        
        SmartArray arr2 = arr1;
        std::cout << "arr2 (copy of arr1) elements: ";
        for (size_t i = 0; i < arr2.getSize(); ++i) {
            std::cout << arr2.getElement(i) << " ";
        }
        std::cout << std::endl;

      
        arr2.addElement(999);
        std::cout << "After modifying arr2:\n";
        std::cout << "arr1 elements: ";
        for (size_t i = 0; i < arr1.getSize(); ++i) {
            std::cout << arr1.getElement(i) << " ";
        }
        std::cout << "\narr2 elements: ";
        for (size_t i = 0; i < arr2.getSize(); ++i) {
            std::cout << arr2.getElement(i) << " ";
        }
        std::cout << std::endl;

        
        SmartArray arr3(2);
        arr3.addElement(44);
        arr3.addElement(34);

        std::cout << "Before assignment, arr3 elements: ";
        for (size_t i = 0; i < arr3.getSize(); ++i) {
            std::cout << arr3.getElement(i) << " ";
        }
        std::cout << std::endl;

        arr3 = arr1; 

        std::cout << "After assignment, arr3 elements: ";
        for (size_t i = 0; i < arr3.getSize(); ++i) {
            std::cout << arr3.getElement(i) << " ";
        }
        std::cout << std::endl;

        
        arr1.addElement(888);
        std::cout << "After modifying arr1:\n";
        std::cout << "arr1 elements: ";
        for (size_t i = 0; i < arr1.getSize(); ++i) {
            std::cout << arr1.getElement(i) << " ";
        }
        std::cout << "\narr3 elements: ";
        for (size_t i = 0; i < arr3.getSize(); ++i) {
            std::cout << arr3.getElement(i) << " ";
        }
        std::cout << std::endl;

    }
    catch (const std::exception& ex) {
        std::cout << "Error: " << ex.what() << std::endl;
    }
}

int main() {
    testCopying();
    return 0;
}