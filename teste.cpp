#include <climits>
#include <iostream>
#include <tuple>
#include <vector>
using namespace std;

tuple<int, int, int> max_crossing_mid(int l, int r, int mid, const vector<int>& arr) {
    int s1 = INT_MIN;
    int l1 = -1;
    int s = 0;
    for (int i = mid; i >= l; --i) {
        s += arr[i];
        if (s > s1) {
            s1 = s;
            l1 = i;
        }
    }

    int s2 = INT_MIN;
    int r2 = -1;
    s = 0;
    for (int i = mid + 1; i <= r; ++i) {
        s += arr[i];
        if (s > s2) {
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

    if (get<2>(a1) > get<2>(a2) && get<2>(a1) > get<2>(a3))
        return a1;
    else if (get<2>(a2) > get<2>(a3))
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