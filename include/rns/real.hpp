#pragma once
#include <vector>
#include "rational.hpp"

class Real 
{
private:
    // Коэффициенты цепной дроби [a_0, a_1, ..., a_k]
    // Для иррациональных чисел это конечный срез бесконечной последовательности
    std::vector<long int> coeffs; 

public:
    // Конструктор 1: Приближение вещественного числа (с ограничением по шагам)
    Real(long double value, int max_terms = 20);
    
    // Конструктор 2: Задание иррационального числа через заранее известные коэффициенты
    Real(std::vector<long int> known_coeffs);

    // Получить n-ую подходящую дробь (рациональное приближение по рекуррентным формулам)
    Rational getConvergent(int n) const;

    // Вывести представление в виде цепной дроби
    void PrintContinuedFraction() const;
    
    // Геттер для доступа к коэффициентам
    const std::vector<long int>& getCoeffs() const { return coeffs; }
};