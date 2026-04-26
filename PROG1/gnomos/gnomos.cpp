#include <iostream>
#include <vector>
using namespace std;

int binSearch(const vector<pair<int, int>>& range, int score, int left, int right) {
    if (score < range[left].first)
        return range[left - 1].second;  // Pontuação abaixo da faixa mínima

    if (score >= range[right].first)
        return range[right].second;  // Pontuação acima ou igual da faixa máxima

    int result = -1;

    // Caso base
    if (right == left)
        return range[left].second;

    int mid = (left + right) / 2;

    if (range[mid].first == score)
        return range[mid].second;

    if (range[mid].first < score)
        result = binSearch(range, score, mid + 1, right);
    else
        result = binSearch(range, score, left, mid);

    return result;
}

vector<int> calculateScore(const vector<pair<int, int>>& range, const vector<int>& arrScores) {
    vector<int> results;

    // Para cada pontuação (m)
    for (int score : arrScores)
        results.push_back(binSearch(range, score, 0, range.size() - 1));

    return results;
}

int main() {
    int n, m;  // n: número de faixas, m: número de pontuações a serem avaliadas
    cin >> n >> m;

    vector<pair<int, int>> range(n);  // vetor de pares (faixa mínima, pontuação correspondente)
    range[0].first = 1;               // A primeira faixa começa em 1

    for (int i = 1; i < n; ++i)
        cin >> range[i].first;

    for (int i = 0; i < n; ++i)
        cin >> range[i].second;

    vector<int> arrScores(m);

    for (int i = 0; i < m; ++i)
        cin >> arrScores[i];

    vector<int> results = calculateScore(range, arrScores);  // calcula as pontuações correspondentes para cada pontuação de entrada

    for (int i = 0; i < m; i++) {
        if (i > 0) cout << " ";
        cout << results[i];
    }
    cout << endl;
}