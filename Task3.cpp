#include <iostream>
#include <vector>
using namespace std;

class RC4 {
    vector<unsigned char> S;
    int i = 0, j = 0;
public:
    RC4(vector<unsigned char> key) {
        S.resize(256);
        for (int i = 0; i < 256; i++) S[i] = i;
        for (int i = 0, j = 0; i < 256; i++) {
            j = (j + S[i] + key[i % key.size()]) % 256;
            swap(S[i], S[j]);
        }
    }
    
    unsigned char generate() {
        i = (i + 1) % 256;
        j = (j + S[i]) % 256;
        swap(S[i], S[j]);
        return S[(S[i] + S[j]) % 256];
    }
};

int main() {
    RC4 rc4({0x01, 0x23, 0x45, 0x67, 0x89, 0xAB, 0xCD, 0xEF});
    
    cout << "Сгенерированные байты: ";
    for (int i = 0; i < 20; i++) {
        printf("%02x ", rc4.generate());
    }
}
