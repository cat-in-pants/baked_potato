#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>

int main() {
    std::vector<int> vec = {4, 7, 2, 9, 5, 1, 8, 3, 6, 10};

    int sum = std::accumulate(vec.begin(), vec.end(), 0);
    std::cout << "Сумма: " << sum << std::endl;

    int product = std::accumulate(vec.begin(), vec.end(), 1, std::multiplies<int>());
    std::cout << "Произведение: " << product << std::endl;

    auto [min, max] = std::minmax_element(vec.begin(), vec.end());
    std::cout << "Разница max-min: " << *max - *min << std::endl;

    return 0;
}