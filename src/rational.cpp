#include <iostream>
#include <numeric>
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
    long int num_gcd = std::gcd(std::abs(a.getM()), std::abs(b.getM()));
    long int den_lcm = std::lcm(a.getN(), b.getN());
    return Rational(num_gcd, den_lcm);
}