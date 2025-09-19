#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cctype>
#include <stdexcept>

class big_integer {
private:
    std::vector<int> digits;
    bool is_negative;

public:
    big_integer(const std::string& str = "0") : is_negative(false) {
        if (str.empty()) {
            digits.push_back(0);
            return;
        }

        size_t start = 0;
        if (str[0] == '-') {
            is_negative = true;
            start = 1;
        }
        else if (str[0] == '+') {
            start = 1;
        }

        if (start >= str.size()) {
            throw std::invalid_argument("Invalid number string: " + str);
        }

        for (size_t i = start; i < str.size(); ++i) {
            if (!std::isdigit(static_cast<unsigned char>(str[i]))) {
                throw std::invalid_argument("Invalid character in number: " + str);
            }
        }

        for (int i = static_cast<int>(str.size()) - 1; i >= static_cast<int>(start); --i) {
            digits.push_back(str[i] - '0');
        }

        remove_leading_zeros();

        if (digits.size() == 1 && digits[0] == 0) {
            is_negative = false;
        }
    }

    big_integer(const big_integer& other) = default;

    big_integer& operator=(const big_integer& other) = default;

    big_integer(big_integer&& other) noexcept
        : digits(std::move(other.digits)), is_negative(other.is_negative) {
        other.digits = { 0 };
        other.is_negative = false;
    }

    big_integer& operator=(big_integer&& other) noexcept {
        if (this != &other) {
            digits = std::move(other.digits);
            is_negative = other.is_negative;
            other.digits = { 0 };
            other.is_negative = false;
        }
        return *this;
    }

    big_integer operator+(const big_integer& other) const {
        if (is_negative != other.is_negative) {
            throw std::runtime_error("Addition of numbers with different signs not implemented");
        }

        big_integer result;
        result.digits.clear();
        result.is_negative = is_negative;

        int carry = 0;
        size_t max_size = std::max(digits.size(), other.digits.size());

        for (size_t i = 0; i < max_size || carry; ++i) {
            int sum = carry;
            if (i < digits.size()) sum += digits[i];
            if (i < other.digits.size()) sum += other.digits[i];

            result.digits.push_back(sum % 10);
            carry = sum / 10;
        }

        result.remove_leading_zeros();
        return result;
    }

    big_integer operator*(int multiplier) const {
        if (multiplier == 0) {
            return big_integer("0");
        }

        big_integer result;
        result.digits.clear();
        result.is_negative = (is_negative != (multiplier < 0));

        int abs_multiplier = std::abs(multiplier);
        int carry = 0;

        for (size_t i = 0; i < digits.size() || carry; ++i) {
            int product = carry;
            if (i < digits.size()) {
                product += digits[i] * abs_multiplier;
            }

            result.digits.push_back(product % 10);
            carry = product / 10;
        }

        result.remove_leading_zeros();
        return result;
    }

    friend std::ostream& operator<<(std::ostream& os, const big_integer& num) {
        if (num.is_negative) {
            os << '-';
        }
        for (int i = static_cast<int>(num.digits.size()) - 1; i >= 0; --i) {
            os << num.digits[i];
        }
        return os;
    }

private:
    void remove_leading_zeros() {
        while (digits.size() > 1 && digits.back() == 0) {
            digits.pop_back();
        }
        if (digits.empty()) {
            digits.push_back(0);
            is_negative = false;
        }
    }
};

void test_big_integer() {
    try {
        auto number1 = big_integer("114575");
        auto number2 = big_integer("78524");
        auto result = number1 + number2;
        std::cout << "114575 + 78524 = " << result << std::endl;

        auto multiplied = big_integer("999") * 5;
        std::cout << "999 * 5 = " << multiplied << std::endl;

        big_integer num1("12345");
        big_integer num2 = std::move(num1);
        std::cout << "After move: " << num2 << std::endl;

        big_integer zero("0");
        std::cout << "Zero: " << zero << std::endl;

        big_integer big1("12345678901234567890");
        big_integer big2("98765432109876543210");
        auto big_sum = big1 + big2;
        std::cout << "Big sum: " << big_sum << std::endl;

    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    try {
        big_integer invalid("12a34");
        std::cout << "This should not print" << std::endl;
    }
    catch (const std::exception& e) {
        std::cout << "Correctly caught error: " << e.what() << std::endl;
    }
}

int main() {
    test_big_integer();
    return 0;
}