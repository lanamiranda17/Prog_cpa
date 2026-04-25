#include <iostream>
#include <vector>
using namespace std;

void calculate_route (int qtd_pontos, vector<int>niceness){

}

int main(){

    int qtd_viagens, qtd_pontos;
    cin >> qtd_viagens;

    while (qtd_viagens > 0){
        cin >> qtd_pontos;
        vector <int> niceness (qtd_pontos-1);

        for (int i=0; i<qtd_pontos; i++){
            cin >> niceness[i];
        }

        calculate_route(qtd_pontos, niceness);
        qtd_viagens--;
    }

}