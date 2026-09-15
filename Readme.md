# Real Number from Scratch

Учебный C++20-проект, демонстрирующий представление рациональных и вещественных чисел через **цепные дроби**.

Проект реализует:

- `Rational` — рациональное число с нормализацией, сокращением дроби и разложением в конечную цепную дробь.
- `Real` — приближение вещественного числа конечным срезом цепной дроби.
- Демонстрационное приложение для приближения числа π и построения подходящих дробей.

## Возможности

- Нормализация рациональных чисел: сокращение дроби, положительный знаменатель.
- Вычисление НОД и НОК для рациональных чисел.
- Разложение рационального числа в цепную дробь через алгоритм Евклида.
- Построение цепной дроби вещественного числа из `long double`.
- Задание иррационального числа через известные коэффициенты цепной дроби.
- Вычисление подходящих дробей по рекуррентным формулам.
- Демо с историческими приближениями числа π: Архимед, Метьюс.

## Структура проекта

```text
real_number_from_scratch/
├── app/
│   ├── CMakeLists.txt
│   └── main.cpp
├── include/
│   └── rns/
│       ├── rational.hpp
│       └── real.hpp
├── src/
│   ├── CMakeLists.txt
│   ├── rational.cpp
│   └── real.cpp
├── tests/
│   └── CmakeLists.txt
├── CMakeLists.txt
├── CMakePresets.json
└── Readme.md
```

## Требования

- C++20
- CMake 3.20+
- Ninja
- MinGW / MSYS2 — для готовых пресетов `mingw-debug` и `mingw-release`

## Сборка

Проект использует `CMakePresets.json`.

### Debug-сборка

```bash
cmake --preset mingw-debug
cmake --build --preset mingw-debug-build
```

### Release-сборка

```bash
cmake --preset mingw-release
cmake --build --preset mingw-release-build
```

В release-сборке тесты отключаются через `BUILD_TESTS=OFF`.

## Запуск

После debug-сборки:

```bash
./build/mingw-debug/app/rns_app.exe
```

После release-сборки:

```bash
./build/mingw-release/app/rns_app.exe
```

На Linux/macOS имя исполняемого файла будет без `.exe`.

## Пример использования

```cpp
#include <iostream>
#include "rns/rational.hpp"
#include "rns/real.hpp"

int main()
{
    // Приближение π через long double
    Real r1(3.141592653589793238L, 10);
    r1.PrintContinuedFraction();

    // Точные коэффициенты цепной дроби π
    std::vector<long int> pi_coeffs = {3, 7, 15, 1, 292, 1, 1, 1, 2, 1};
    Real r2(pi_coeffs);

    // Подходящая дробь: приближение Метьюса 355/113
    Rational metius = r2.getConvergent(4);

    std::cout << metius.getM() << "/" << metius.getN() << std::endl;
}
```

## Основной API

### `Rational`

```cpp
Rational(long int m, long int n);
Rational();

long int getM() const;
long int getN() const;

void Print() const;
```

Дополнительные функции:

```cpp
Rational gcd_formula(const Rational& a, const Rational& b);

std::vector<long int> toContinuedFraction(const Rational& r);
```

### `Real`

```cpp
Real(long double value, int max_terms = 20);
Real(std::vector<long int> known_coeffs);

Rational getConvergent(int n) const;
void PrintContinuedFraction() const;

const std::vector<long int>& getCoeffs() const;
```

## Математическая основа

Число представляется цепной дробью:

```text
x = [a₀; a₁, a₂, a₃, ...]
```

Подходящие дроби вычисляются по рекуррентным формулам:

```text
p₋₂ = 0, p₋₁ = 1
q₋₂ = 1, q₋₁ = 0

pᵢ = aᵢ · pᵢ₋₁ + pᵢ₋₂
qᵢ = aᵢ · qᵢ₋₁ + qᵢ₋₂
```

Подходящая дробь:

```text
pᵢ / qᵢ
```

Для рационального числа цепная дробь конечна и получается через алгоритм Евклида.  
Для иррационального числа цепная дробь бесконечна, поэтому в проекте хранится её конечный срез.

## Демонстрация

Приложение `rns_app` показывает:

- разложение π через `long double`;
- разложение π через точные коэффициенты;
- таблицу подходящих дробей;
- ошибку приближения;
- исторические приближения:
  - Архимед: `22/7`
  - Метьюс: `355/113`

## Тесты

Каталог `tests` пока является заготовкой.  
Для включения тестов используется опция CMake:

```bash
cmake -DBUILD_TESTS=ON ...
```

## Планы развития

- Добавить unit-тесты.
- Реализовать арифметические операции для `Rational`.
- Добавить сравнение рациональных чисел.
- Расширить работу с цепными дробями.
- Добавить поддержку больших целых чисел.
- Улучшить обработку точности для `Real`.