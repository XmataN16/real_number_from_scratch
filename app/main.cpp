#include <iostream>
#include <iomanip>
#include <vector>
#include "rns/rational.hpp"
#include "rns/real.hpp"

int main() 
{
    std::cout << std::fixed << std::setprecision(15);

    std::cout << "=== DEMO APPROXIMATION NUMBER PI ===\n" << std::endl;

    // Способ 1: Алгоритм сам "вычисляет" коэффициенты из long double
    long double pi_approx = 3.141592653589793238L;
    Real r1(pi_approx, 10); // Просим алгоритм найти 10 коэффициентов
    
    std::cout << "1. Decomposition via long double:" << std::endl;
    std::cout << "Continued fraction: "; r1.PrintContinuedFraction();
    
    std::cout << "\nThe process of constructing a Dedekind cut (convergents):" << std::endl;
    std::cout << "---------------------------------------------------------" << std::endl;
    std::cout << "Step | Convergent | Value          | Error" << std::endl;
    std::cout << "---------------------------------------------------------" << std::endl;
    
    for (size_t i = 0; i < r1.getCoeffs().size(); ++i) {
        Rational conv = r1.getConvergent(i);
        long double val = static_cast<long double>(conv.getM()) / conv.getN();
        long double error = std::abs(pi_approx - val);
        
        std::cout << "  " << i << " | " 
                  << std::setw(5) << conv.getM() << "/" << std::left << std::setw(5) << conv.getN() << " | " 
                  << val << " | " << std::scientific << error << std::fixed << std::endl;
    }

    // Способ 2: Мы задаем иррациональное число "сверху" через его истинные коэффициенты
    // Первые коэффициенты Пи: [3; 7, 15, 1, 292, 1, 1, 1, 2, 1, 3, 1, 14, 2, ...]
    std::vector<long int> pi_exact_coeffs = {3, 7, 15, 1, 292, 1, 1, 1, 2, 1, 3, 1, 14, 2};
    Real r2(pi_exact_coeffs);
    
    std::cout << "\n2. Decomposition via precise mathematical coefficients:" << std::endl;
    std::cout << "Continued fraction: "; r2.PrintContinuedFraction();
    
    // Получаем знаменитое приближение Архимеса (шаг 1) и приближение Метьюса (шаг 4)
    Rational archimedes = r2.getConvergent(1);
    Rational metius = r2.getConvergent(4);
    
    std::cout << "\nHistorical approximations:" << std::endl;
    std::cout << "Archimedes' approximation (step 1): " << archimedes.getM() << "/" << archimedes.getN() 
              << " = " << static_cast<long double>(archimedes.getM()) / archimedes.getN() << std::endl;
              
    std::cout << "Matthews' approximation (step 4) " << metius.getM() << "/" << metius.getN() 
              << " = " << static_cast<long double>(metius.getM()) / metius.getN() << std::endl;

    return 0;
}