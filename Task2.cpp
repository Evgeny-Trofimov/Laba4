#include <iostream>   
#include <iomanip>    
#include <vector>     
#include <random>     
#include <algorithm> 

using namespace std;

// Функция для генерации случайного вещественного числа в диапазоне [min, max]
double randomDouble(double min, double max) {
    static random_device rd;
    static mt19937 gen(rd());
    uniform_real_distribution<double> dis(min, max);
    return dis(gen);
}

// Функция для вывода массива по 6 элементов в строку
void printArray(const vector<double> arr, const string title) {
    std::cout << title << ":\n";
    for (size_t i = 0; i < arr.size(); ++i) {
        cout << setw(8) << arr[i];
        if ((i + 1) % 6 == 0) cout << '\n';
    }
    std::cout << '\n';
}

int main() {
    // 1. Создание и инициализация массива случайными вещественными числами
    const int n = 15;  // n >= 10
    vector<double> arr(n);
    for (double& num : arr) {
        num = randomDouble(-100.0, 100.0);
    }
    printArray(arr, "Исходный массив");

    // 2. Подсчет положительных элементов и суммы после последнего нуля
    int positiveCount = 0;
    for (double num : arr) {
        if (num > 0) ++positiveCount;
    }
    cout << "Количество положительных элементов: " << positiveCount << '\n';

    // Находим последний ноль
    auto lastZero = find(arr.rbegin(), arr.rend(), 0.0);
    double sumAfterLastZero = 0.0;
    if (lastZero != arr.rend()) {
        // Суммируем элементы после последнего нуля
        auto it = lastZero.base();  // Итератор на элемент после нуля
        for (; it != arr.end(); ++it) {
            sumAfterLastZero += *it;
        }
    }
    cout << "Сумма элементов после последнего нуля: " << sumAfterLastZero << '\n';

    // 3. Поиск самой длинной возрастающей последовательности
    vector<double> longestIncreasing;
    vector<double> currentSeq;
    for (size_t i = 0; i < arr.size(); ++i) {
        if (currentSeq.empty() || arr[i] > currentSeq.back()) {
            currentSeq.push_back(arr[i]);
        } else {
            if (currentSeq.size() > longestIncreasing.size()) {
                longestIncreasing = currentSeq;
            }
            currentSeq.clear();
            currentSeq.push_back(arr[i]);
        }
    }
    // Проверяем последнюю последовательность
    if (currentSeq.size() > longestIncreasing.size()) {
        longestIncreasing = currentSeq;
    }
    printArray(longestIncreasing, "Самая длинная возрастающая последовательность");

    // 4. Вывод массива длиной N×6 по 6 элементов в строку
    const int N = 4;
    const int totalElements = N * 6;
    vector<int> outputArr(totalElements);
    outputArr[0] = 100;
    for (int i = 1; i < totalElements; ++i) {
        outputArr[i] = outputArr[i - 1] + 1;
    }
    cout << "Массив длиной " << totalElements << ":\n";
    for (int i = 0; i < totalElements; ++i) {
        cout << setw(4) << outputArr[i];
        if ((i + 1) % 6 == 0) cout << '\n';
    }
    
    const int N1=8;
    const int totalElements1 = N1 * 6;
    vector<int> outputArr1(totalElements1);
    outputArr1[0] = 100;
    for (int i = 1; i < totalElements1; ++i) {
        outputArr1[i] = outputArr1[i - 1] + 1;
    }
    cout << "Массив длиной " << totalElements1 << ":\n";
    for (int i = 0; i < totalElements1; ++i) {
        cout << setw(4) << outputArr1[i];
        if ((i + 1) % 6 == 0) cout << '\n';
    }

    return 0;
}
