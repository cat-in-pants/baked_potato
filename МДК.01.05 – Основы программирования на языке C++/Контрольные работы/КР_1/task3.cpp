#include <iostream>
#include <fstream>
#include <vector>
#include <numeric>

int main() {
    std::ofstream outFile("numbers.txt");
    for (int i = 1; i <= 5; ++i) {
        outFile << i * 10 << " ";
    }
    outFile.close();

    std::ifstream inFile("numbers.txt");
    std::vector<int> numbers;
    int num;
    while (inFile >> num) {
        numbers.push_back(num);
    }
    inFile.close();

    double avg = std::accumulate(numbers.begin(), numbers.end(), 0.0) / numbers.size();
    std::cout << "Среднее: " << avg << std::endl;

    return 0;
}