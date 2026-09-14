#include <iostream>
#include "rns/rational.hpp"

void printContinuedFraction(const std::vector<long int>& coeffs) 
{
    if (coeffs.empty()) return;
    std::cout << "[" << coeffs[0];
    if (coeffs.size() > 1) {
        std::cout << "; ";
        for (size_t i = 1; i < coeffs.size(); ++i) {
            std::cout << coeffs[i];
            if (i < coeffs.size() - 1) std::cout << ", ";
        }
    }
    std::cout << "]" << std::endl;
}

int main() {
    try {
        // Тест 1: Пример из вашего документа (1071 / 462)
        Rational r1(1071, 462);
        std::cout << "number 1: "; r1.Print();
        
        auto cf1 = toContinuedFraction(r1);
        std::cout << "Continued fraction: ";
        printContinuedFraction(cf1);
        
        // Тест 2: Отрицательное число (-3 / 2)
        // Математически: -1.5 = -2 + 0.5 = -2 + 1/2 -> [-2; 2]
        Rational r2(-3, 2);
        std::cout << "\nnumber 2: "; r2.Print();
        
        auto cf2 = toContinuedFraction(r2);
        std::cout << "Continued fraction: ";
        printContinuedFraction(cf2);

        // Тест 3: Обычная дробь (22 / 7)
        Rational r3(22, 7);
        std::cout << "\nnumber 3: "; r3.Print();
        
        auto cf3 = toContinuedFraction(r3);
        std::cout << "Continued fraction: ";
        printContinuedFraction(cf3);

    } 
    catch (const std::exception& e) 
    {
        std::cerr << "Error: " << e.what() << std::endl;
    }
    return 0;
}