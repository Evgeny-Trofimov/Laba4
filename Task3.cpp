#include <iostream>
#include <vector>
using namespace std;

// Класс, реализующий алгоритм шифрования RC4
class RC4 {
    vector<unsigned char> S;  // Вектор состояния (S-блок) размером 256 байт
    int i = 0, j = 0;         // Индексы для генерации псевдослучайных байт

public:
    // Конструктор класса, инициализирует S-блок на основе ключа
    RC4(vector<unsigned char> key) {
        S.resize(256);  // Устанавливаем размер S-блока
        
        // Инициализация S-блока 
        // 1. Заполняем S-блок значениями от 0 до 255
        for (int i = 0; i < 256; i++) {
            S[i] = i;
        }
        
        // 2. Перемешиваем S-блок на основе ключа
        for (int i = 0, j = 0; i < 256; i++) {
            // Вычисляем новый индекс j с использованием ключа
            j = (j + S[i] + key[i % key.size()]) % 256;
            // Меняем местами элементы S[i] и S[j]
            swap(S[i], S[j]);
        }
    }
    
    // Метод генерации псевдослучайного байта 
    unsigned char generate() {
        // Обновляем индексы i и j
        i = (i + 1) % 256;
        j = (j + S[i]) % 256;
        
        // Меняем местами элементы S[i] и S[j]
        swap(S[i], S[j]);
        
        // Возвращаем псевдослучайный байт из S-блока
        return S[(S[i] + S[j]) % 256];
    }
};

int main() {
    // Создаем объект RC4 с тестовым ключом (8 байт)
    RC4 rc4({0x01, 0x23, 0x45, 0x67, 0x89, 0xAB, 0xCD, 0xEF});
    
    // Генерируем и выводим первые 20 псевдослучайных байт
    cout << "Сгенерированные байты: ";
    for (int i = 0; i < 20; i++) {
        // Выводим каждый байт в шестнадцатеричном формате 
        printf("%02x ", rc4.generate());
    }
    
    return 0;
}
