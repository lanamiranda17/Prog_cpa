#include <iostream>
#include <vector>
using namespace std;

/*
    Solução de divisão e conquista para calcular o número mínimo de operações necessárias para o flip sort
    ordenar o vetor (corresponde ao número de inversões).
    Usa merge sort modificado para contar o número de inversões.

*/

// Faz o merge de duas metades ordenadas e conta inversões entre elas.
int merge(vector<int>& A, int inicio, int meio, int fim) {
    int n1 = meio - inicio + 1;
    int n2 = fim - meio;

    vector<int> L(n1);
    vector<int> R(n2);

    for (int i = 0; i < n1; i++) {
        L[i] = A[inicio + i];
    }

    for (int j = 0; j < n2; j++) {
        R[j] = A[meio + 1 + j];
    }

    int i = 0;
    int j = 0;
    int k = inicio;
    int inversoes = 0;

    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            A[k] = L[i];
            i++;
        } else {
            A[k] = R[j];
            j++;

            inversoes += n1 - i;  // contabiliza todos os elementos restantes de L, pois todos formam inversão com R[j-1] já que o vetor está ordenado
        }
        k++;
    }

    // Copia os elementos restantes de L e R, se houver
    while (i < n1) {
        A[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        A[k] = R[j];
        j++;
        k++;
    }

    return inversoes;
}

int mergeSort(vector<int>& A, int inicio, int fim) {
    if (inicio >= fim) {
        return 0;
    }

    int meio = (inicio + fim) / 2;

    int inversoes = 0;

    inversoes += mergeSort(A, inicio, meio);
    inversoes += mergeSort(A, meio + 1, fim);
    inversoes += merge(A, inicio, meio, fim);

    return inversoes;
}

int main() {
    int n;
    cin >> n;

    while (n > 0) {
        vector<int> A(n);

        for (int i = 0; i < n; i++) {
            cin >> A[i];
        }

        cout << "Minimum exchange operations : " << mergeSort(A, 0, n - 1) << endl;

        cin >> n;
    }
}
