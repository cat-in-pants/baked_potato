#include <iostream>
#include <fstream>
#include <stdexcept>
#include <string>

double div(double a, double b) {
    if (b == 0.0) {
        throw std::invalid_argument("деление на 0");
    }
    return a / b;
}

void readFile(std::string name) {
    std::ifstream f(name);
    if (!f.is_open()) {
        throw std::runtime_error("нетю файла");
    }
    std::string s;
    while (std::getline(f, s)) {
        std::cout << s << '\n';
    }
    f.close();
}

int getPositive(int x) {
    if (x <= 0) {
        throw std::invalid_argument("отриц число");
    }
    return x;
}

void f3() {
    throw std::runtime_error("ошибка");
}

void f2() {
    f3();
}

void f1() {
    f2();
}

int main() {
    try {
        div(10.0, 0.0);
    } catch (const std::exception& e) {
        std::cout << e.what() << '\n';
    }

    try {
        readFile("1.txt");
    } catch (const std::exception& e) {
        std::cout << e.what() << '\n';
    }

    try {
        getPositive(-5);
    } catch (const std::exception& e) {
        std::cout << e.what() << '\n';
    }

    try {
        f1();
    } catch (const std::exception& e) {
        std::cout << e.what() << '\n';
    }

    return 0;
} 
