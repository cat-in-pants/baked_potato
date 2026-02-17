#include <iostream>
#include <string>
#include <sstream>
#include <stdexcept>

int main() {
    std::cout << "Введите число: ";
    std::string input;
    std::getline(std::cin, input);

    try {
        std::stringstream ss(input);
        int number;
        if (!(ss >> number)) {
            throw std::invalid_argument("Это не число");
        }

        if (number < 0) {
            throw std::runtime_error("Число отрицательное");
        }

        std::cout << "Вы ввели: " << number << std::endl;

    } catch (const std::exception& e) {
        std::cerr << "Ошибка: " << e.what() << std::endl;
    }

    return 0;
}