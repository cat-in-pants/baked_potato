#include <iostream>
#include <string>
#include <string_view>
#include <vector>
#include <cctype>
#include <cstdlib>

size_t count_words(std::string_view str) {
    size_t count = 0;
    bool in_word = false;
    
    for (char c : str) {
        if (std::isspace(c)) {
            in_word = false;
        } else {
            if (!in_word) {
                count++;
                in_word = true;
            }
        }
    }
    
    return count;
}

std::vector<std::string_view> split(std::string_view str) {
    std::vector<std::string_view> result;
    size_t start = 0;
    
    while (start < str.size()) {
        while (start < str.size() && std::isspace(str[start])) {
            start++;
        }
        
        size_t end = start;
        while (end < str.size() && !std::isspace(str[end])) {
            end++;
        }
        
        if (start < str.size()) {
            result.push_back(str.substr(start, end - start));
        }
        
        start = end;
    }
    
    return result;
}

bool is_palindrome(std::string_view str) {
    size_t i = 0;
    size_t j = str.size() - 1;
    
    while (i < j) {
        while (i < j && !std::isalnum(str[i])) i++;
        while (i < j && !std::isalnum(str[j])) j--;
        
        if (std::tolower(str[i]) != std::tolower(str[j])) {
            return false;
        }
        
        i++;
        j--;
    }
    
    return true;
}

int sum_values(std::string_view str) {
    int sum = 0;
    size_t start = 0;
    
    while (start < str.size()) {
        size_t eq_pos = str.find('=', start);
        if (eq_pos == std::string_view::npos) break;
        
        size_t end = str.find(';', eq_pos);
        if (end == std::string_view::npos) {
            end = str.size();
        }
        
        std::string_view num_str = str.substr(eq_pos + 1, end - eq_pos - 1);
        sum += std::stoi(std::string(num_str));
        
        start = end + 1;
    }
    
    return sum;
}

std::string_view longest_word(std::string_view str) {
    std::string_view longest;
    size_t start = 0;
    
    while (start < str.size()) {
        while (start < str.size() && std::isspace(str[start])) {
            start++;
        }
        
        size_t end = start;
        while (end < str.size() && !std::isspace(str[end])) {
            end++;
        }
        
        if (start < str.size()) {
            std::string_view word = str.substr(start, end - start);
            if (word.size() > longest.size()) {
                longest = word;
            }
        }
        
        start = end;
    }
    
    return longest;
}

int main() {
    std::string test_string = "  meow meow mewo  ";
    std::string palindrome_test = "meow meow woem woem";
    std::string values_string = "x=10;y=20;z=30";
    
    std::cout << "1. слова: " << count_words(test_string) << std::endl;
    
    auto words = split(test_string);
    std::cout << "2. разделение: ";
    for (auto w : words) std::cout << "'" << w << "' ";
    std::cout << std::endl;
    
    std::cout << "3. палиндром: " << (is_palindrome(palindrome_test) ? "д" : "н") << std::endl;
    
    std::cout << "4. сумма: " << sum_values(values_string) << std::endl;
    
    std::cout << "5. длинное слово: '" << longest_word(test_string) << "'" << std::endl;
    
    return 0;
}
