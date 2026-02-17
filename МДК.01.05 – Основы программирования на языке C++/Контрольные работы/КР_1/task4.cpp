#include <iostream>
#include <chrono>

int main() {
    auto start = std::chrono::steady_clock::now();
    volatile int dummy;
    for (int i = 0; i < 10'000'000; ++i) {
        dummy = i;
    }
    auto end = std::chrono::steady_clock::now();
    auto ms1 = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    std::cout << "Первый цикл: " << ms1 << " ms" << std::endl;

    start = std::chrono::steady_clock::now();
    for (int i = 0; i < 10'000'000; ++i) {
        dummy = i * i;
    }
    end = std::chrono::steady_clock::now();
    auto ms2 = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    std::cout << "Второй цикл: " << ms2 << " ms" << std::endl;

    std::cout << "Разница: " << (ms2 - ms1) << " ms" << std::endl;

    return 0;
}