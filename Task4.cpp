#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <algorithm>

using namespace std;

// Структура для хранения информации о кандидате
struct Candidate {
    string name;
    int borda_score;
    map<string, int> condorcet_wins; // Количество побед над другими кандидатами
};

// Функция для подсчета очков по методу Борда
void calculateBordaScores(vector<Candidate>& candidates, const vector<vector<string>>& votes) {
    int n = candidates.size();
    
    // Обнуляем все очки
    for (auto& c : candidates) {
        c.borda_score = 0;
    }
    
    // Для каждого голоса
    for (const auto& vote : votes) {
        // Для каждой позиции в голосе
        for (int pos = 0; pos < vote.size(); ++pos) {
            // Находим кандидата и добавляем ему очки
            for (auto& c : candidates) {
                if (c.name == vote[pos]) {
                    c.borda_score += (n - pos - 1);
                    break;
                }
            }
        }
    }
}

// Функция для определения победителя по методу Борда
string findBordaWinner(const vector<Candidate>& candidates) {
    int max_score = -1;
    string winner;
    
    for (const auto& c : candidates) {
        if (c.borda_score > max_score) {
            max_score = c.borda_score;
            winner = c.name;
        }
    }
    
    return winner;
}

// Функция для парных сравнений по методу Кондорсе
void calculateCondorcetWins(vector<Candidate>& candidates, const vector<vector<string>>& votes) {
    // Инициализация счетчиков побед
    for (auto& c1 : candidates) {
        for (const auto& c2 : candidates) {
            if (c1.name != c2.name) {
                c1.condorcet_wins[c2.name] = 0;
            }
        }
    }
    
    // Для каждого голоса
    for (const auto& vote : votes) {
        // Сравниваем каждую пару кандидатов
        for (int i = 0; i < vote.size(); ++i) {
            for (int j = i + 1; j < vote.size(); ++j) {
                string first = vote[i];
                string second = vote[j];
                
                // Увеличиваем счетчик побед для кандидата, который выше в списке
                for (auto& c : candidates) {
                    if (c.name == first) {
                        c.condorcet_wins[second]++;
                    }
                }
            }
        }
    }
}

// Функция для определения победителя по методу Кондорсе
string findCondorcetWinner(const vector<Candidate>& candidates) {
    int n = candidates.size();
    int total_voters = 0;
    
    // Находим количество избирателей (можно было бы передавать как параметр)
    if (!candidates.empty() && !candidates[0].condorcet_wins.empty()) {
        total_voters = candidates[0].condorcet_wins.begin()->second;
        for (const auto& c : candidates) {
            for (const auto& pair : c.condorcet_wins) {
                total_voters = max(total_voters, pair.second);
            }
        }
    }
    
    // Ищем кандидата, который побеждает всех остальных
    for (const auto& c : candidates) {
        bool is_winner = true;
        
        for (const auto& opponent : candidates) {
            if (c.name != opponent.name) {
                // Если есть кандидат, которого наш кандидат не побеждает
                if (c.condorcet_wins.at(opponent.name) <= total_voters / 2) {
                    is_winner = false;
                    break;
                }
            }
        }
        
        if (is_winner) {
            return c.name;
        }
    }
    
    return "Нет победителя по Кондорсе";
}

int main() {
    // Ввод данных
    int n, k;
    cout << "Введите количество кандидатов: ";
    cin >> n;
    cout << "Введите количество избирателей: ";
    cin >> k;
    cin.ignore(); // Очищаем буфер после ввода чисел
    
    vector<Candidate> candidates(n);
    cout << "Введите имена кандидатов (по одному в строке):\n";
    for (int i = 0; i < n; ++i) {
        getline(cin, candidates[i].name);
    }
    
    vector<vector<string>> votes(k);
    cout << "Введите голоса избирателей (каждый голос - список имен через пробел):\n";
    for (int i = 0; i < k; ++i) {
        string line;
        getline(cin, line);
        
        size_t pos = 0;
        string token;
        while ((pos = line.find(' ')) != string::npos) {
            token = line.substr(0, pos);
            votes[i].push_back(token);
            line.erase(0, pos + 1);
        }
        if (!line.empty()) {
            votes[i].push_back(line);
        }
    }
    
    // Подсчет результатов по методу Борда
    calculateBordaScores(candidates, votes);
    string borda_winner = findBordaWinner(candidates);
    
    // Подсчет результатов по методу Кондорсе
    calculateCondorcetWins(candidates, votes);
    string condorcet_winner = findCondorcetWinner(candidates);
    
    // Вывод результатов
    cout << "\nРезультаты:\n";
    cout << "Метод Борда:\n";
    for (const auto& c : candidates) {
        cout << c.name << ": " << c.borda_score << " очков\n";
    }
    cout << "Победитель по Борда: " << borda_winner << "\n\n";
    
    cout << "Метод Кондорсе:\n";
    cout << "Победитель по Кондорсе: " << condorcet_winner << "\n";
    
    // Анализ результатов
    if (borda_winner != condorcet_winner && condorcet_winner != "Нет победителя по Кондорсе") {
        cout << "\nПримечание: разные методы дали разных победителей. "
             << "Это демонстрирует, что результаты выборов могут зависеть "
             << "от используемого метода подсчета.\n";
    }
    
    return 0;
}
