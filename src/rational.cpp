#include <iostream>
#include "rns/rational.hpp"

void Rational::Print()
{
    std::cout << this->m << "/" << this->n << std::endl;
}