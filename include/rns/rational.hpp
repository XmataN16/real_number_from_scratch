#pragma once

class Rational 
{    
    long int m;
    long int n;

public:
    Rational(long int m, long int n)
    {
        this->m = m;
        this->n = n;
    }

    // Конструктор по умолчанию
    Rational()
    {
        this->m = 0;
        this->n = 1;
    }

    void Print();
};