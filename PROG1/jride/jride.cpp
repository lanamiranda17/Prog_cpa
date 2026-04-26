#include <iostream>
#include <vector>
using namespace std;

int main() {
    int m;  // quantidade de viagens
    cin >> m;

    for (int r = 1; r <= m; ++r) {
        int n;  // quantidade de pontos de parada
        cin >> n;

        int current_sum = 0;
        int current_start = 0;

        int best_sum = 0;
        int best_start = 0;
        int best_end = 0;

        for (int i = 0; i < n - 1; i++) {  // n-1 porque niceness é entre os pontos de parada
            int niceness;
            cin >> niceness;

            current_sum += niceness;

            int tamanho_atual = i - current_start + 1;  // +1 para contar o número de paradas
            int melhor_tamanho = best_end - best_start + 1;

            if (current_sum > best_sum ||                                                                      // se nova soma é melhor,
                (current_sum == best_sum && tamanho_atual > melhor_tamanho) ||                                 // ou se soma é igual, mas tamanho maior,
                (current_sum == best_sum && tamanho_atual == melhor_tamanho && current_start < best_start)) {  // ou se soma e tamanho são iguais, mas início é menor

                // Atualiza o melhor resultado encontrado
                best_sum = current_sum;
                best_start = current_start;
                best_end = i;
            }

            if (current_sum < 0) {
                current_sum = 0;
                current_start = i + 1;
            }
        }

        if (best_sum > 0) {
            // Converte índices de trechos para paradas: trecho i vai da parada i+1 até i+2.
            cout << "The nicest part of route " << r << " is between stops " << best_start + 1 << " and " << best_end + 2 << endl;
        } else {
            cout << "Route " << r << " has no nice parts" << endl;
        }
    }
}