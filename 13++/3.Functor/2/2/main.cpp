#include <iostream>
#include <vector>
#include <stdexcept>

template<typename T>
class Table {
private:
    std::vector<std::vector<T>> data;
    size_t rows;
    size_t cols;

public:
    Table(size_t num_rows, size_t num_cols)
        : rows(num_rows), cols(num_cols)
    {
        data.resize(rows);
        for (size_t i = 0; i < rows; ++i) {
            data[i].resize(cols);
        }
    }

    std::vector<T>& operator[](size_t row_index) {
        if (row_index >= rows) {
            throw std::out_of_range("Row index out of range");
        }
        return data[row_index];
    }

    const std::vector<T>& operator[](size_t row_index) const {
        if (row_index >= rows) {
            throw std::out_of_range("Row index out of range");
        }
        return data[row_index];
    }

    std::pair<size_t, size_t> Size() const {
        return { rows, cols };
    }
};

int main() {
    Table<int> test(2, 3);

    test[0][0] = 4;
    test[0][1] = 5;
    test[0][2] = 6;
    test[1][0] = 7;
    test[1][1] = 8;
    test[1][2] = 9;

    std::cout << test[0][0] << std::endl; 
    std::cout << test[1][2] << std::endl;

    auto size = test.Size();
    std::cout << "Table size: " << size.first << " x " << size.second << std::endl;

    const Table<int>& const_table = test;
    std::cout << "Const access: " << const_table[0][1] << std::endl; 


    return 0;
}