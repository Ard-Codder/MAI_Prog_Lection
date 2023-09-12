// Напишите программу, которая поможет рассчитать номер варианта. Оформите вычисление варианта в виде функции.

// Вариант 1.
// Номер варианта – остаток от деления суммы всех букв фамилии на число вариантов.


#include <iostream>
#include <string>

int calculateVariant(const std::string& surname, int numOfVariants) {
    int sum = 0;
    for (char c : surname) {
        sum += static_cast<int>(c);
    }
    return (sum % numOfVariants) + 1;
}

int main() {
    std::string surname;
    int numOfVariants;

    std::cout << "Enter your surname: ";
    std::cin >> surname;

    std::cout << "Enter the number of variants: ";
    std::cin >> numOfVariants;

    int variant = calculateVariant(surname, numOfVariants);
    std::cout << "Variant number: " << variant << std::endl;

    return 0;
}
