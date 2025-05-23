#include <iostream>   
#include <iomanip>    
#include <vector>     
#include <random>     
#include <algorithm>  

using namespace std;  // Используем стандартное пространство имен

// Функция для генерации случайного вещественного числа в диапазоне [min, max]
double randomDouble(double min, double max) {
    static random_device rd;  // Источник энтропии
    static mt19937 gen(rd());  // Генератор случайных чисел
    uniform_real_distribution<double> dis(min, max);  // Равномерное распределение
    return dis(gen);  // Возвращаем случайное число
}

// Функция для вывода массива по 6 элементов в строку
void printArray(const vector<double> arr, const string title) {
    cout << title << ":\n";  // Выводим заголовок
    for (size_t i = 0; i < arr.size(); ++i) {
        cout << setw(8) << arr[i];  // Выводим элемент с отступом
        if ((i + 1) % 6 == 0) cout << '\n';  // Перенос строки каждые 6 элементов
    }
    cout << '\n';  // Дополнительный перенос в конце
}

// Функция для вывода массива в двух вариантах 
void printSpecialArray(int N) {
    const int totalElements = N * 6;  // Всего элементов (N строк по 6 элементов)
    vector<int> arr(totalElements);   // Создаем массив
    
    // Заполняем массив последовательными числами начиная с 100
    arr[0] = 100;
    for (int i = 1; i < totalElements; i++) {
        arr[i] = arr[i-1] + 1;
    }
    
    // Вывод заголовков таблицы
    cout << "N = " << N << endl;
    cout << setw(15) << "Вывод 1" << setw(25) << "Вывод 2" << endl;
    
    // Вывод массивов построчно
    for (int i = 0; i < N; i++) {
        // Вывод 1 - обычный порядок (всегда слева)
        for (int j = 0; j < 6; j++) {
            cout << setw(4) << arr[i*6 + j];
        }
        
        cout << "         ";  // Разделитель между выводами
        
        // Вывод 2 - для нечетных строк обратный порядок
        if (i % 2 == 0) {
            // Четные строки (0, 2, 4...) - обычный порядок
            for (int j = 0; j < 6; j++) {
                cout << setw(4) << arr[i*6 + j];
            }
        } else {
            // Нечетные строки (1, 3, 5...) - обратный порядок
            for (int j = 5; j >= 0; j--) {
                cout << setw(4) << arr[i*6 + j];
            }
        }
        
        cout << endl;  // Перенос строки после каждой строки вывода
    }
    cout << endl;  // Дополнительный перенос после всего вывода
}

int main() {
    // 1. Создание и инициализация массива случайными вещественными числами
    const int n = 15;  // Размер массива (должен быть >= 10)
    vector<double> arr(n);  // Создаем вектор из n элементов
    
    // Заполняем массив случайными числами от -100.0 до 100.0
    for (double& num : arr) {
        num = randomDouble(-100.0, 100.0);
    }
    printArray(arr, "Исходный массив");  // Выводим исходный массив

    // 2. Подсчет положительных элементов и суммы после последнего нуля
    int positiveCount = 0;  // Счетчик положительных элементов
    
    // Считаем количество положительных элементов
    for (double num : arr) {
        if (num > 0) ++positiveCount;
    }
    cout << "Количество положительных элементов: " << positiveCount << '\n';

    // Находим последний ноль в массиве (ищем с конца)
    auto lastZero = find(arr.rbegin(), arr.rend(), 0.0);
    double sumAfterLastZero = 0.0;  // Сумма элементов после последнего нуля
    
    // Если ноль найден, суммируем элементы после него
    if (lastZero != arr.rend()) {
        // Получаем итератор на элемент после нуля
        auto it = lastZero.base();
        // Суммируем все элементы до конца массива
        for (; it != arr.end(); ++it) {
            sumAfterLastZero += *it;
        }
    }
    cout << "Сумма элементов после последнего нуля: " << sumAfterLastZero << '\n';

    // 3. Поиск самой длинной возрастающей последовательности
    vector<double> longestIncreasing;  // Самая длинная последовательность
    vector<double> currentSeq;        // Текущая последовательность
    
    // Проходим по всем элементам массива
    for (size_t i = 0; i < arr.size(); ++i) {
        // Если последовательность пуста или текущий элемент больше последнего в последовательности
        if (currentSeq.empty() || arr[i] > currentSeq.back()) {
            currentSeq.push_back(arr[i]);  // Добавляем элемент в последовательность
        } else {
            // Если текущая последовательность длиннее самой длинной, обновляем
            if (currentSeq.size() > longestIncreasing.size()) {
                longestIncreasing = currentSeq;
            }
            currentSeq.clear();          // Очищаем текущую последовательность
            currentSeq.push_back(arr[i]);  // Начинаем новую последовательность
        }
    }
    // Проверяем последнюю последовательность (она могла быть самой длинной)
    if (currentSeq.size() > longestIncreasing.size()) {
        longestIncreasing = currentSeq;
    }
    printArray(longestIncreasing, "Самая длинная возрастающая последовательность");

    // 4. Вывод массива длиной N×6 по 6 элементов в строку в специальном формате
    // Вывод для N = 4 и N = 8
    printSpecialArray(4);
    printSpecialArray(8);

    return 0;  // Завершение программы
}
