#include "rns/real.hpp"
#include <cmath>
#include <iostream>
#include <stdexcept>

// Конструктор от вещественного числа (алгоритм генерации коэффициентов)
Real::Real(long double value, int max_terms) {
    long double x = value;
    // Порог точности для long double (машинный эпсилон)
    const long double EPS = 1e-14; 

    for (int i = 0; i < max_terms; ++i) {
        // 1. Вычисляем i-й коэффициент (целая часть)
        long double a = std::floor(x);
        coeffs.push_back(static_cast<long int>(a));

        // 2. Вычисляем дробную часть
        long double frac = x - a;
        
        // Критерий остановки: если дробная часть исчезающе мала, 
        // значит число оказалось рациональным в пределах точности
        if (std::abs(frac) < EPS) {
            break; 
        }
        
        // 3. Инвертируем дробную часть для следующего шага
        x = 1.0 / frac;
    }
}

// Конструктор от известных коэффициентов (для "точных" иррациональных чисел)
Real::Real(std::vector<long int> known_coeffs) : coeffs(known_coeffs) {}

// Алгоритм вычисления подходящих дробей
Rational Real::getConvergent(int n) const {
    if (n < 0 || n >= static_cast<int>(coeffs.size())) {
        throw std::out_of_range("Индекс выходит за пределы известных коэффициентов");
    }

    // Начальные условия для рекуррентных формул
    long int p_prev2 = 0, p_prev1 = 1;
    long int q_prev2 = 1, q_prev1 = 0;

    for (int i = 0; i <= n; ++i) {
        long int a = coeffs[i];
        
        // Рекуррентные формулы
        long int p_curr = a * p_prev1 + p_prev2;
        long int q_curr = a * q_prev1 + q_prev2;

        // Сдвиг для следующей итерации
        p_prev2 = p_prev1;
        p_prev1 = p_curr;
        q_prev2 = q_prev1;
        q_prev1 = q_curr;
    }

    // p_prev1 и q_prev1 теперь содержат числитель и знаменатель n-ой подходящей дроби
    return Rational(p_prev1, q_prev1);
}

void Real::PrintContinuedFraction() const {
    if (coeffs.empty()) {
        std::cout << "[]" << std::endl;
        return;
    }
    std::cout << "[" << coeffs[0];
    if (coeffs.size() > 1) {
        std::cout << "; ";
        for (size_t i = 1; i < coeffs.size(); ++i) {
            std::cout << coeffs[i];
            if (i < coeffs.size() - 1) std::cout << ", ";
        }
    }
    std::cout << ", ...]" << std::endl; 
}