#include <iostream>

int gcd(int a, int b)
{
    if (b == 0)
        return a;
    return gcd(b, a % b);
}

class Fraction
{
private:
    int numerator_;
    int denominator_;

public:
    Fraction(int numerator, int denominator)
    {
        int common = gcd(numerator, denominator);
        numerator_ = numerator / common;
        denominator_ = denominator / common;
    }

    Fraction operator+(const Fraction& other) const
    {
        int new_numerator = (numerator_ * other.denominator_) + (other.numerator_ * denominator_);
        int new_denominator = denominator_ * other.denominator_;
        return Fraction(new_numerator, new_denominator);
    }

    Fraction operator-(const Fraction& other) const
    {
        int new_numerator = (numerator_ * other.denominator_) - (other.numerator_ * denominator_);
        int new_denominator = denominator_ * other.denominator_;
        return Fraction(new_numerator, new_denominator);
    }

    Fraction operator*(const Fraction& other) const
    {
        int new_numerator = numerator_ * other.numerator_;
        int new_denominator = denominator_ * other.denominator_;
        return Fraction(new_numerator, new_denominator);
    }

    Fraction operator/(const Fraction& other) const
    {
        int new_numerator = numerator_ * other.denominator_;
        int new_denominator = denominator_ * other.numerator_;
        return Fraction(new_numerator, new_denominator);
    }

    Fraction operator-() const
    {
        return Fraction(-numerator_, denominator_);
    }

    Fraction& operator++() 
    {
        numerator_ += denominator_;
        return *this;
    }

    Fraction operator++(int) 
    {
        Fraction temp = *this;
        numerator_ += denominator_;
        return temp;
    }

    Fraction& operator--() 
    {
        numerator_ -= denominator_;
        return *this;
    }

    Fraction operator--(int) 
    {
        Fraction temp = *this;
        numerator_ -= denominator_;
        return temp;
    }

    bool operator==(const Fraction& other) const
    {
        return (numerator_ == other.numerator_ && denominator_ == other.denominator_);
    }

    bool operator!=(const Fraction& other) const
    {
        return !(*this == other);
    }

    bool operator<(const Fraction& other) const
    {
        return (numerator_ * other.denominator_ < other.numerator_ * denominator_);
    }

    bool operator>(const Fraction& other) const
    {
        return (numerator_ * other.denominator_ > other.numerator_ * denominator_);
    }

    bool operator<=(const Fraction& other) const
    {
        return (*this < other || *this == other);
    }

    bool operator>=(const Fraction& other) const
    {
        return (*this > other || *this == other);
    }

    friend std::ostream& operator<<(std::ostream& os, const Fraction& fraction)
    {
        os << fraction.numerator_ << "/" << fraction.denominator_;
        return os;
    }
};

int main()
{

    setlocale(LC_ALL, "Russian");

    int num1, den1, num2, den2;

    std::cout << "Введите числитель дроби 1: ";
    std::cin >> num1;
    std::cout << "Введите знаменатель дроби 1: ";
    std::cin >> den1;

    std::cout << "Введите числитель дроби 2: ";
    std::cin >> num2;
    std::cout << "Введите знаменатель дроби 2: ";
    std::cin >> den2;

    Fraction f1(num1, den1);
    Fraction f2(num2, den2);

    std::cout << f1 << " + " << f2 << " = " << f1 + f2 << '\n';
    std::cout << f1 << " - " << f2 << " = " << f1 - f2 << '\n';
    std::cout << f1 << " * " << f2 << " = " << f1 * f2 << '\n';
    std::cout << f1 << " / " << f2 << " = " << f1 / f2 << '\n';

    std::cout << "++" << f1 << " = " << ++f1 << '\n';
    std::cout << "Значение дроби 1 = " << f1 << '\n';
    std::cout << f1-- << " * " << f2 << " = " << f1-- * f2 << '\n';
    std::cout << "Значение дроби 1 = " << f1 << '\n';

    return 0;
}