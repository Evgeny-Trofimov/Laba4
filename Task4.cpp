#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <algorithm>

using namespace std;

// Функция для метода Борда
string borda(vector<vector<string>> votes) {
    if (votes.empty()) return "Нет голосов";
    
    map<string, int> scores;
    int candidates_count = votes[0].size();
    
    for (auto vote : votes) {
        for (int i = 0; i < vote.size(); i++) {
            scores[vote[i]] += candidates_count - i - 1;
        }
    }
    
    string winner;
    int max_score = -1;
    for (auto [candidate, score] : scores) {
        if (score > max_score) {
            max_score = score;
            winner = candidate;
        }
    }
    
    return winner;
}

// Функция для метода Кондорсе
string condorcet(vector<vector<string>> votes) {
    if (votes.empty()) return "Нет голосов";
    
    vector<string> candidates = votes[0];
    
    for (string candidate : candidates) {
        bool wins_all = true;
        
        for (string opponent : candidates) {
            if (candidate == opponent) continue;
            
            int wins = 0;
            for (auto vote : votes) {
                auto c_pos = find(vote.begin(), vote.end(), candidate);
                auto o_pos = find(vote.begin(), vote.end(), opponent);
                if (c_pos < o_pos) wins++;
            }
            
            if (wins <= votes.size() / 2) {
                wins_all = false;
                break;
            }
        }
        
        if (wins_all) return candidate;
    }
    
    return "Нет победителя";
}

int main() {
    // Пример голосования 
    vector<vector<string>> votes = {
        {"Вася", "Оля", "Петя"},
        {"Вася", "Оля", "Петя"},
        {"Оля", "Петя", "Вася"},
        {"Оля", "Вася", "Петя"},
        {"Петя", "Вася", "Оля"}
    };
    
    string borda_winner = borda(votes);
    string condorcet_winner = condorcet(votes);
    
    cout << "Метод Борда: " << borda_winner << endl;
    cout << "Метод Кондорсе: " << condorcet_winner << endl;
    
    if (borda_winner != condorcet_winner) {
        cout << "Примечание: Методы дали разные результаты!" << endl;
    }
    
    return 0;
}
