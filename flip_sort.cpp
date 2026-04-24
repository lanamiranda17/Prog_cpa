#include <iostream>
using namespace std;

int merge(int *A, int inicio, int meio, int fim) {
    int n1 = meio - inicio + 1;
    int n2 = fim - meio;

    int *L = new int[n1];
    int *R = new int[n2];

    for (int i = 0; i < n1; i++) {
        L[i] = A[inicio + i];
    }

    for (int j = 0; j < n2; j++) {
        R[j] = A[meio + 1 + j];
    }

    int i = 0, j = 0, k = inicio;
    int inversoes = 0;

    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            A[k] = L[i];
            i++;
        } else {
            A[k] = R[j];
            j++;

            inversoes += n1 - i;
        }
        k++;
    }

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

    delete[] L;
    delete[] R;

    return inversoes;
}

int mergeSort(int *A, int inicio, int fim) {
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

int main (){

    int n;
    cin >> n;
    while (n > 0) {

        int* A = new int[n];
        for (int i=0; i<n; i++){
            cin >> A[i];
        }

        cout << "Minimum exchange operations : " << mergeSort(A, 0, n-1) << endl;

        cin >> n;
    }

}
