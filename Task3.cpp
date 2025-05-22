#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class RC4 {
private:
    vector<unsigned char> S;  // Таблица замен (state)
    unsigned int i, j;            // Счетчики
    unsigned int n;                // Параметр n (размер слова)
    unsigned int size;             // Размер таблицы (2^n)

public:
    // Конструктор с инициализацией ключом
    RC4(unsigned int n, const vector<unsigned char> key) : n(n) {
        size = 1 << n;  // Вычисляем 2^n
        S.resize(size);
        
        // 1. Инициализация таблицы замен (KSA - Key Scheduling Algorithm)
        for (unsigned int i = 0; i < size; ++i) {
            S[i] = i;
        }
        
        unsigned int j = 0;
        for (unsigned int i = 0; i < size; ++i) {
            j = (j + S[i] + key[i % key.size()]) % size;
            swap(S[i], S[j]);
        }
        
        // Инициализация счетчиков
        this->i = 0;
        this->j = 0;
    }
    
    // Генерация псевдослучайного байта (PRGA - Pseudo-Random Generation Algorithm)
    unsigned char generate() {
        i = (i + 1) % size;
        j = (j + S[i]) % size;
        swap(S[i], S[j]);
        unsigned char t = (S[i] + S[j]) % size;
        return S[t];
    }
    
    // Генерация нескольких байт
    vector<unsigned char> generateBytes(unsigned int count) {
        vector<unsigned char> result(count);
        for (unsigned int k = 0; k < count; ++k) {
            result[k] = generate();
        }
        return result;
    }
};

int main() {
    // Пример использования
    
    // Параметры
    unsigned int n = 8;  // Размер слова (8 бит)
    vector<unsigned char> key = {0x01, 0x23, 0x45, 0x67, 0x89, 0xAB, 0xCD, 0xEF};  // Ключ
    
    // Инициализация генератора
    RC4 rc4(n, key);
    
    // Генерация 20 псевдослучайных байт
    auto randomBytes = rc4.generateBytes(20);
    
    // Вывод результатов
    cout << "Сгенерированные байты: ";
    for (unsigned char byte : randomBytes) {
        cout << std::hex << (int)byte << " ";
    }
    cout << endl;
    
    return 0;
}
