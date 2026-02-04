#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <random>

using namespace std;
using namespace chrono;

vector<int> generateArray(int size) {
    vector<int> arr(size);
    mt19937 rng(random_device{}());
    uniform_int_distribution<int> dist(1, 1000000);
    for (int i = 0; i < size; i++) {
        arr[i] = dist(rng);
    }
    return arr;
}

int fibRec(int n) {
    if (n <= 1) return n;
    return fibRec(n - 1) + fibRec(n - 2);
}

int fibIter(int n) {
    if (n <= 1) return n;
    int a = 0, b = 1, c;
    for (int i = 2; i <= n; i++) {
        c = a + b;
        a = b;
        b = c;
    }
    return b;
}

void a() {
    vector<int> arr = generateArray(100000);
    auto start = steady_clock::now();
    sort(arr.begin(), arr.end());
    auto end = steady_clock::now();
    auto time = duration_cast<milliseconds>(end - start);
    cout << "время сорт: " << time.count() << " мс\n";
}

void b() {
    vector<int> arr = generateArray(10000);
    vector<int> bubbleArr = arr;
    auto start = steady_clock::now();
    sort(arr.begin(), arr.end());
    auto end = steady_clock::now();
    auto sortTime = duration_cast<milliseconds>(end - start);
    cout << "сорт: " << sortTime.count() << " мс\n";
    start = steady_clock::now();
    for (size_t i = 0; i < bubbleArr.size() - 1; i++) {
        bool swapped = false;
        for (size_t j = 0; j < bubbleArr.size() - i - 1; j++) {
            if (bubbleArr[j] > bubbleArr[j + 1]) {
                swap(bubbleArr[j], bubbleArr[j + 1]);
                swapped = true;
            }
        }
        if (!swapped) break;
    }
    end = steady_clock::now();
    auto bubbleTime = duration_cast<milliseconds>(end - start);
    cout << "пузырёк: " << bubbleTime.count() << " мс\n";
}

void c() {
    vector<int> arr = generateArray(100000);
    sort(arr.begin(), arr.end());
    int target = arr[50000];
    auto start = steady_clock::now();
    auto it = find(arr.begin(), arr.end(), target);
    auto end = steady_clock::now();
    auto linearTime = duration_cast<microseconds>(end - start);
    cout << "лин: " << linearTime.count() << " мкс\n";
    start = steady_clock::now();
    bool found = binary_search(arr.begin(), arr.end(), target);
    end = steady_clock::now();
    auto binaryTime = duration_cast<microseconds>(end - start);
    cout << "бинар: " << binaryTime.count() << " мкс\n";
}

void d() {
    int n = 40;
    auto start = steady_clock::now();
    int resRec = fibRec(n);
    auto end = steady_clock::now();
    auto recTime = duration_cast<milliseconds>(end - start);
    cout << "рекур: " << recTime.count() << " мс\n";
    start = steady_clock::now();
    int resIter = fibIter(n);
    end = steady_clock::now();
    auto iterTime = duration_cast<microseconds>(end - start);
    cout << "итер: " << iterTime.count() << " мкс\n";
}

void e() {
    vector<int> arr = generateArray(50000);
    long long total = 0;
    int runs = 5;
    for (int i = 0; i < runs; i++) {
        vector<int> copyArr = arr;
        auto start = steady_clock::now();
        sort(copyArr.begin(), copyArr.end());
        auto end = steady_clock::now();
        total += duration_cast<microseconds>(end - start).count();
    }
    cout << "среднее: " << total / runs << " мс\n";
}

int main() {
    a();
    b();
    c();
    d();
    e();
    return 0;
}
