#include <climits>
#include <iostream>
#include <tuple>
#include <vector>
using namespace std;

/*
    Solução usando o algoritmo de Divide and conquer para encontrar a subarray de soma máxima.
    Complexidade: O(m * n log n) em tempo e O(n) em espaço, onde m é o número de viagens e n é o número de pontos de parada.
*/

int tamanho(const tuple<int, int, int>& trecho) {
    return get<1>(trecho) - get<0>(trecho) + 1;
}

// Função para comparar duas tuplas de acordo com as regras do problema
bool melhor_que(const tuple<int, int, int>& a, const tuple<int, int, int>& b) {
    int soma_a = get<2>(a);
    int soma_b = get<2>(b);

    if (soma_a != soma_b)
        return soma_a > soma_b;

    int tam_a = tamanho(a);
    int tam_b = tamanho(b);

    if (tam_a != tam_b)
        return tam_a > tam_b;

    return get<0>(a) < get<0>(b);
}

tuple<int, int, int> max_crossing_mid(int l, int r, int mid, const vector<int>& arr) {
    int s1 = INT_MIN;
    int l1 = mid;
    int s = 0;

    for (int i = mid; i >= l; --i) {
        s += arr[i];

        if (s > s1 || (s == s1 && i < l1)) {  // atualiza se encontrar uma soma maior ou, em caso de empate, um índice menor (maior extensão)
            s1 = s;
            l1 = i;
        }
    }

    int s2 = INT_MIN;
    int r2 = mid + 1;
    s = 0;

    for (int i = mid + 1; i <= r; ++i) {
        s += arr[i];

        if (s > s2 || (s == s2 && i > r2)) {
            s2 = s;
            r2 = i;
        }
    }

    return make_tuple(l1, r2, s1 + s2);
}

tuple<int, int, int> max_sum_subArr(int l, int r, const vector<int>& arr) {
    // Caso base
    if (l == r)
        return make_tuple(l, r, arr[l]);

    int mid = (l + r) / 2;

    tuple<int, int, int> a1 = max_sum_subArr(l, mid, arr);
    tuple<int, int, int> a2 = max_sum_subArr(mid + 1, r, arr);
    tuple<int, int, int> a3 = max_crossing_mid(l, r, mid, arr);

    if (melhor_que(a1, a2) && melhor_que(a1, a3))
        return a1;
    else if (melhor_que(a2, a3))
        return a2;
    else
        return a3;
}

tuple<int, int, int> calculate_route(int qtd_pontos, const vector<int>& niceness) {
    return max_sum_subArr(0, qtd_pontos - 2, niceness);
}

int main() {
    int qtd_viagens;
    cin >> qtd_viagens;

    for (int r = 1; r <= qtd_viagens; ++r) {
        int qtd_pontos;
        cin >> qtd_pontos;

        vector<int> niceness(qtd_pontos - 1);

        for (int i = 0; i < qtd_pontos - 1; i++) {
            cin >> niceness[i];
        }

        tuple<int, int, int> ans = calculate_route(qtd_pontos, niceness);

        if (get<2>(ans) <= 0)
            cout << "Route " << r << " has no nice parts" << endl;
        else
            cout << "The nicest part of route " << r << " is between stops " << get<0>(ans) + 1 << " and " << get<1>(ans) + 2 << endl;
    }
}