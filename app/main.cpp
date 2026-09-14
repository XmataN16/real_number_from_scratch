#include <iostream>
#include "rns/rational.hpp"

int main() {
    try {
        Rational r1(5, 6);
        Rational r2(7, 15);

        std::cout << "number 1: "; r1.Print();
        std::cout << "number 2: "; r2.Print();

        Rational res = gcd_formula(r1, r2);
        std::cout << "GCD: "; res.Print();

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}