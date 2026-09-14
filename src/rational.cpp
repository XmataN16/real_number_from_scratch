#include <iostream>
#include <numeric>
#include <vector>
#include "rns/rational.hpp"

void Rational::Print() const
{
    std::cout << this->m << "/" << this->n << std::endl;
}

void Rational::normalize() {
    if (n == 0) {
        throw std::invalid_argument("Знаменатель не может быть равен нулю");
    }
    if (n < 0) {
        m = -m;
        n = -n;
    }
    long int g = std::gcd(std::abs(m), std::abs(n));
    m /= g;
    n /= g;
}

Rational::Rational(long int m, long int n) : m(m), n(n) 
{
    normalize();
}

Rational::Rational() : m(0), n(1) {}

Rational gcd_formula(const Rational& a, const Rational& b) 
{
    long int num_gcd = std::gcd(std::abs(a.getM()), std::abs(b.getM())); // Находим НОД числителей
    long int den_lcm = std::lcm(a.getN(), b.getN()); // Находим НОК знаменателей
    return Rational(num_gcd, den_lcm);
}

// Реализация алгоритма разложения в цепную дробь
std::vector<long int> toContinuedFraction(const Rational& r) 
{
    std::vector<long int> coeffs;
    long int num = r.getM();
    long int den = r.getN(); // Благодаря normalize() знаменатель всегда > 0
    
    // Вспомогательная лямбда-функция для математического floor (округления вниз)
    // В C++ деление целых чисел работает "к нулю", а нам нужно строго "вниз"
    auto floorDiv = [](long int a, long int b) -> long int 
    {
        long int res = a / b;
        long int rem = a % b;
        // Если есть остаток и он имеет другой знак, чем делитель (b > 0, значит rem < 0)
        if (rem != 0 && ((rem < 0 && b > 0) || (rem > 0 && b < 0))) 
        {
            res -= 1; // Корректируем в сторону минус бесконечности
        }
        return res;
    };

    // Цикл алгоритма Евклида
    while (den != 0) 
    {
        // 1. Вычислить коэффициент (частное): a_i = floor(num / den)
        long int a = floorDiv(num, den);
        coeffs.push_back(a);
        
        // 2. Вычислить следующий остаток: r_{i+2} = num mod den
        // Мы используем num - a * den, чтобы гарантировать, что остаток всегда >= 0
        long int rem = num - a * den; 
        
        // Переход к следующему шагу
        num = den;
        den = rem;
    }
    
    return coeffs;
}