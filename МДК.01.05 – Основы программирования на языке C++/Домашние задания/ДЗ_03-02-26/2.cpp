#include <iostream>
#include <fstream>
#include <string>
#include <vector>

void a() {
    std::ifstream fin("numbers.txt");
    if (!fin.is_open()) {
        std::cout << "файла нетю\n";
        return;
    }
    double sum = 0, num;
    int count = 0;
    
    while (fin >> num) {
        sum += num;
        count++;
    }
    fin.close();
    std::cout << "среднее: " << (count > 0 ? sum / count : 0) << std::endl;
}

void bc() {
    std::ifstream fin("text.txt");
    if (!fin.is_open()) {
        std::cout << "файла нетю\n";
        return;
    }
    std::string line;
    int lines = 0;
    std::string longest;
    
    while (std::getline(fin, line)) {
        lines++;
        if (line.length() > longest.length()) {
            longest = line;
        }
    }
    fin.close();
    std::cout << "строки:  " << lines << std::endl;
    std::cout << "самая длинная:  " << longest.length() << std::endl;
}

void d() {
    std::ifstream fin("source.txt");
    std::ofstream fout("copy.txt");
    if (!fin.is_open() || !fout.is_open()) {
        std::cout << "файла нетю\n";
        return;
    }
    std::string line;
    while (std::getline(fin, line)) {
        fout << line << "\n";
    }
    fin.close();
    fout.close();
}

void e() {
    std::ifstream fin("input.txt");
    std::ofstream fout("output.txt");
    if (!fin.is_open() || !fout.is_open()) {
        std::cout << "файла нетю\n";
        return;
    }
    char ch;
    while (fin.get(ch)) {
        if (ch == ' ') {
            fout << '_';
        } else {
            fout << ch;
        }
    }
    fin.close();
    fout.close();
}

int main() {
    a();
    bc();
    d();
    e();
    
    return 0;
}