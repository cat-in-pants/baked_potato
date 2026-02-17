#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <set>

int main() {
    std::string input = "apple,banana,orange,apple,kiwi";
    std::vector<std::string> words;
    std::stringstream ss(input);
    std::string word;

    while (std::getline(ss, word, ',')) {
        size_t start = word.find_first_not_of(" ");
        size_t end = word.find_last_not_of(" ");
        if (start != std::string::npos && end != std::string::npos) {
            words.push_back(word.substr(start, end - start + 1));
        }
    }

    std::set<std::string> uniqueSet(words.begin(), words.end());
    words.assign(uniqueSet.begin(), uniqueSet.end());

    std::sort(words.begin(), words.end());

    for (const auto& w : words) {
        std::cout << w << std::endl;
    }

    return 0;
}