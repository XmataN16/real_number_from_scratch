#pragma once

class Rational 
{    
    long int m;
    long int n;

    // Функция нормализации (сокращение дроби и положительный знаменатель)
    void normalize();

public:
    Rational(long int m, long int n);

    // Конструктор по умолчанию
    Rational();

    // Геттеры для доступа к полям извне
    long int getM() const { return m; }
    long int getN() const { return n; }

    void Print() const;
};

Rational gcd_formula(const Rational& a, const Rational& b);