#define _CRT_SECURE_NO_WARNINGS 
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <map>
#include <algorithm>
#include <set>
#include <limits>
#include <clocale>
#include <windows.h>
#include <iomanip>
#include <cstdio>
#include <filesystem> 
#include <chrono>     
#include <ctime>      

using namespace std;
namespace fs = std::filesystem;

enum class TransactionType {
    Income,
    Expense
};

struct Transaction {
    int id;
    TransactionType type;
    string category;
    double amount;
    string date;
    std::string description;
};

struct TableWidths {
    int id;
    int type;
    int category;
    int amount;
    int date;
    int description;
};

vector<Transaction> transactions;
int nextId = 1;

string currentFileName = "finance_data.txt";

void clearInputBuffer() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

string getCurrentDate() {
    auto now = std::chrono::system_clock::now();
    std::time_t now_c = std::chrono::system_clock::to_time_t(now);
    std::tm now_tm = *std::localtime(&now_c);

    char buffer[11];
    std::strftime(buffer, sizeof(buffer), "%Y-%m-%d", &now_tm);
    return string(buffer);
}

wstring utf8ToWstring(const string& str) {
    if (str.empty()) return wstring();
    int size_needed = MultiByteToWideChar(CP_UTF8, 0, &str[0], (int)str.size(), NULL, 0);
    wstring wstrTo(size_needed, 0);
    MultiByteToWideChar(CP_UTF8, 0, &str[0], (int)str.size(), &wstrTo[0], size_needed);
    return wstrTo;
}

int getVisualLength(const string& str) {
    int len = 0;
    for (size_t i = 0; i < str.length(); ++i) {
        if ((str[i] & 0xC0) != 0x80) {
            len++;
        }
    }
    return len;
}

string typeToString(TransactionType type) {
    return (type == TransactionType::Income) ? "Доход" : "Расход";
}

string formatAmount(double amount) {
    char buffer[50];
    sprintf(buffer, "%.2f", amount);
    return string(buffer);
}

vector<string> splitString(const string& str, char delimiter) {
    vector<string> tokens;
    string token;
    for (char c : str) {
        if (c == delimiter) {
            tokens.push_back(token);
            token.clear();
        } else {
            token += c;
        }
    }
    tokens.push_back(token);
    return tokens;
}

bool isValidDate(const string& date) {
    if (date.length() != 10) return false;
    if (date[4] != '-' || date[7] != '-') return false;
    for (int i = 0; i < 10; ++i) {
        if (i == 4 || i == 7) continue;
        if (!isdigit(date[i])) return false;
    }
    return true;
}

void sortTransactionsById() {
    sort(transactions.begin(), transactions.end(), [](const Transaction& a, const Transaction& b) {
        return a.id < b.id;
    });
}

void saveDataToFile() {
    sortTransactionsById(); 

    fs::path filePath(utf8ToWstring(currentFileName));
    ofstream file(filePath);
    
    if (!file.is_open()) {
        cerr << "Ошибка: Не удалось записать в файл!" << endl;
        return;
    }
    for (const auto& t : transactions) {
        file << t.id << "|"
             << (t.type == TransactionType::Income ? "Income" : "Expense") << "|"
             << t.category << "|"
             << t.amount << "|"
             << t.date << "|"
             << t.description << endl;
    }
    file.close();
}

bool loadDataFromFile(const string& filename, bool createIfMissing = false) {
    fs::path filePath(utf8ToWstring(filename));
    ifstream file(filePath);
    
    if (!file.is_open()) {
        if (createIfMissing) {
            ofstream newFile(filePath);
            newFile.close();
            transactions.clear();
            nextId = 1;
            currentFileName = filename;
            return true;
        } else {
            return false;
        }
    }

    transactions.clear();
    
    string line;
    bool foundProblems = false; 
    int lineNum = 0;

    set<int> usedIds;
    int maxIdFound = 0;

    while (getline(file, line)) {
        lineNum++;
        if (line.empty()) continue;

        vector<string> parts = splitString(line, '|');
        
        if (parts.size() < 6) {
            foundProblems = true;
            continue;
        }

        try {
            Transaction t;
            int fileId = stoi(parts[0]);

            if (fileId <= 0 || usedIds.count(fileId)) {
                t.id = -1; 
                foundProblems = true;
            } else {
                t.id = fileId;
                usedIds.insert(fileId);
                if (fileId > maxIdFound) maxIdFound = fileId;
            }

            if (parts[1] == "Income") t.type = TransactionType::Income;
            else if (parts[1] == "Expense") t.type = TransactionType::Expense;
            else throw exception();

            t.category = parts[2];

            t.amount = stod(parts[3]);
            if (t.amount <= 0) throw exception();

            t.date = parts[4];
            if (!isValidDate(t.date)) throw exception();

            t.description = parts[5];

            transactions.push_back(t);

        } catch (...) {
            foundProblems = true;
            continue; 
        }
    }
    file.close();
    
    nextId = maxIdFound + 1;

    for (auto& t : transactions) {
        if (t.id == -1) {
            t.id = nextId++;
        }
    }

    currentFileName = filename;
    sortTransactionsById();

    if (foundProblems) {
        saveDataToFile();
    }

    cout << "Успешно загружено из: " << currentFileName << endl;
    return true;
}

void loadFromCustomFile() {
    string path;
    cout << "Введите полный путь к файлу (или перетащите в это окно):" << endl;
    cout << "> ";
    getline(cin, path);

    if (path.length() >= 2 && path.front() == '"' && path.back() == '"') {
        path = path.substr(1, path.length() - 2);
    }
    if (path.empty()) return;

    if (loadDataFromFile(path, false)) {
    } else {
        cout << "Ошибка: Файл не найден." << endl;
    }
}

void printCell(string text, int width) {
    int visLen = getVisualLength(text);
    cout << text;
    
    int padding = width - visLen;
    for(int i=0; i < padding; ++i) cout << " ";
    
    cout << "   "; 
}

void addTransaction() {
    Transaction t;
    t.id = nextId++;

    cout << "Тип (1-Доход, 2-Расход): ";
    int typeInput;
    while (!(cin >> typeInput) || (typeInput != 1 && typeInput != 2)) {
        clearInputBuffer();
        cout << "1 или 2: ";
    }
    t.type = (typeInput == 1) ? TransactionType::Income : TransactionType::Expense;
    clearInputBuffer();

    cout << "Категория: ";
    getline(cin, t.category);
    if (t.category.empty()) t.category = "Разное";

    cout << "Сумма: ";
    while (!(cin >> t.amount) || t.amount <= 0) {
        clearInputBuffer();
        cout << "Сумма > 0: ";
    }
    clearInputBuffer();

    cout << "Дата (YYYY-MM-DD) [Enter = Сегодня]: ";
    getline(cin, t.date);

    if (t.date.empty()) {
        t.date = getCurrentDate(); 
        cout << "Установлена дата: " << t.date << endl;
    } else {
        while (!isValidDate(t.date)) {
            cout << "Неверный формат! YYYY-MM-DD: ";
            getline(cin, t.date);
        }
    }

    cout << "Описание: ";
    getline(cin, t.description);

    transactions.push_back(t);
    cout << "Успешно добавлено." << endl;
    saveDataToFile();
}

void viewTransactions() {
    if (transactions.empty()) {
        cout << "Список пуст." << endl;
        return;
    }

    cout << "\n1.Все, 2.Доходы, 3.Расходы, 4.Период: ";
    int filterChoice;
    cin >> filterChoice;
    clearInputBuffer();

    string startDate, endDate;
    if (filterChoice == 4) {
        cout << "Начало (YYYY-MM-DD): "; getline(cin, startDate);
        cout << "Конец (YYYY-MM-DD): "; getline(cin, endDate);
    }

    cout << "0.Без сортировки, 1.Дата, 2.Сумма: ";
    int sortType;
    cin >> sortType;
    clearInputBuffer();

    vector<const Transaction*> visibleTransactions;

    for (const auto& t : transactions) {
        bool show = false;
        if (filterChoice == 1) show = true;
        else if (filterChoice == 2 && t.type == TransactionType::Income) show = true;
        else if (filterChoice == 3 && t.type == TransactionType::Expense) show = true;
        else if (filterChoice == 4 && t.date >= startDate && t.date <= endDate) show = true;

        if (show) {
            visibleTransactions.push_back(&t);
        }
    }

    if (visibleTransactions.empty()) {
        cout << "Нет записей по заданным критериям." << endl;
        return;
    }

    if (sortType == 1) { 
        sort(visibleTransactions.begin(), visibleTransactions.end(), [](const Transaction* a, const Transaction* b) {
            return a->date < b->date;
        });
    } else if (sortType == 2) { 
        sort(visibleTransactions.begin(), visibleTransactions.end(), [](const Transaction* a, const Transaction* b) {
            return a->amount < b->amount; 
        });
    }

    TableWidths w;
    w.id = getVisualLength("ID");
    w.type = getVisualLength("Тип");
    w.category = getVisualLength("Категория");
    w.amount = getVisualLength("Сумма");
    w.date = getVisualLength("Дата");
    w.description = getVisualLength("Описание");

    for (const auto* t : visibleTransactions) {
        w.id = max(w.id, getVisualLength(to_string(t->id)));
        w.type = max(w.type, getVisualLength(typeToString(t->type)));
        w.category = max(w.category, getVisualLength(t->category));
        w.amount = max(w.amount, getVisualLength(formatAmount(t->amount)));
        w.date = max(w.date, getVisualLength(t->date));
        w.description = max(w.description, getVisualLength(t->description));
    }

    cout << endl;
    printCell("ID", w.id);
    printCell("Тип", w.type);
    printCell("Категория", w.category);
    printCell("Сумма", w.amount);
    printCell("Дата", w.date);
    printCell("Описание", w.description);
    cout << endl;

    for(int i=0; i < (w.id+w.type+w.category+w.amount+w.date+w.description + 18); i++) cout << "-";
    cout << endl;
    
    for (const auto* t : visibleTransactions) {
        printCell(to_string(t->id), w.id);
        printCell(typeToString(t->type), w.type);
        printCell(t->category, w.category);
        printCell(formatAmount(t->amount), w.amount);
        printCell(t->date, w.date);
        printCell(t->description, w.description);
        cout << endl;
    }
}

void deleteTransaction() {
    int id;
    cout << "ID для удаления: ";
    if (!(cin >> id)) {
        clearInputBuffer();
        return;
    }
    clearInputBuffer();

    auto it = find_if(transactions.begin(), transactions.end(), [id](const Transaction& t) {
        return t.id == id;
    });

    if (it != transactions.end()) {
        transactions.erase(it);
        cout << "Удалено." << endl;
        saveDataToFile(); 
    } else {
        cout << "ID не найден." << endl;
    }
}

void showStatistics() {
    if (transactions.empty()) {
        cout << "Нет данных." << endl;
        return;
    }
    double income = 0, expense = 0;
    map<string, double> cats;
    set<string> months;

    for (const auto& t : transactions) {
        if (t.type == TransactionType::Income) income += t.amount;
        else expense += t.amount;
        cats[t.category] += t.amount;
        if (t.date.length() >= 7) months.insert(t.date.substr(0, 7));
    }

    cout << "\n=== СТАТИСТИКА ===" << endl;
    cout << "Доход:    " << income << endl;
    cout << "Расход:   " << expense << endl;
    cout << "Баланс:   " << (income - expense) << endl;
    if (!months.empty()) cout << "Сред./мес: " << expense / months.size() << endl;
    cout << "------------------" << endl;
    for (auto p : cats) cout << p.first << ": " << p.second << endl;
    cout << "==================" << endl;
}

void showMenu() {
    cout << "\nФайл: " << currentFileName << endl;
    cout << "1. Добавить" << endl;
    cout << "2. Просмотр" << endl;
    cout << "3. Удалить" << endl;
    cout << "4. Статистика" << endl;
    cout << "5. Загрузить из файла" << endl;
    cout << "6. Выйти" << endl;           
    cout << "> ";
}

int main() {
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);
    
    loadDataFromFile("finance_data.txt", true);

    int choice;
    while (true) {
        showMenu();
        if (!(cin >> choice)) {
            clearInputBuffer();
            continue;
        }
        clearInputBuffer();

        switch (choice) {
            case 1: addTransaction(); break;
            case 2: viewTransactions(); break;
            case 3: deleteTransaction(); break;
            case 4: showStatistics(); break;
            case 5: loadFromCustomFile(); break;
            case 6: return 0;
            default: cout << "Неверно." << endl;
        }
    }
}
