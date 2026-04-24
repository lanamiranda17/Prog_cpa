#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

struct Numero
{
    string original;
    vector<int> blocos; // blocos de no máximo 4 dígitos, da direita para a esquerda
};

string removerEspacos(string s)
{
    string resultado = "";

    for (int i = 0; i < s.size(); i++)
    {
        if (s[i] != ' ')
        {
            resultado += s[i];
        }
    }
    return resultado;
}

void counting_sort_blocos(vector<Numero> &contas, int pos, int quant_contas)
{

    vector<Numero> saida(quant_contas);
    vector<int> count(10000, 0); // Base 10000 (cada bloco tem 4 dígitos), tudo começa com 0

    for (int i = 0; i < quant_contas; i++)
    {
        count[contas[i].blocos[pos]]++;
    } // conta quantas vezes cada valor aparece em cada passada (cada bloco)

    for (int i = 1; i < 10000; i++)
    {
        count[i] += count[i - 1]; // Contagem acumulada p/ ficar mais eficiente -> vira vetor de posicoes
    }

    // reconstrói o vetor em ordem crescente
    for (int i = quant_contas - 1; i >= 0; i--)
    {
        int bloco = contas[i].blocos[pos];
        int posicao = count[bloco] - 1;

        saida[posicao] = contas[i];

        count[bloco]--;
    }

    for (int i = 0; i < quant_contas; i++)
    {
        contas[i] = saida[i];
    }
}

void dividir_blocos(string conta, Numero &num)
{
    num.original = conta;
    conta = removerEspacos(conta);
    for (int i = conta.size(); i > 0; i -= 4)
    { // conta.size é sempre 26 e tamanho do bloco é 4

        int inicio = max(0, i - 4);
        int tamanho = i - inicio;
        num.blocos.push_back(stoi(conta.substr(inicio, tamanho)));
    }
    // cout<< "Conta: " << num.original << " Blocos: ";
    // for (int i=0; i<num.blocos.size(); i++){
    //     cout << num.blocos[i] << " ";
    // }
    // cout << endl;
}

void radix_counting_sort(vector<Numero> &contas, int quant_contas)
{

    for (int i = 0; i < quant_contas; i++)
    {
        dividir_blocos(contas[i].original, contas[i]);
    }

    int maior_quant_blocos = 0;
    for (int i = 0; i < quant_contas; i++)
    {
        if (contas[i].blocos.size() > maior_quant_blocos)
        {
            maior_quant_blocos = contas[i].blocos.size();
        }
    }

    for (int pos = 0; pos < maior_quant_blocos; pos++)
    {
        counting_sort_blocos(contas, pos, quant_contas);
    }
}

void imprimir_saida(vector<Numero> &contas, int quant_contas)
{
    int i = 0;

    while (i < quant_contas)
    {
        int qtd = 1;

        while (i + qtd < quant_contas &&
               contas[i].original == contas[i + qtd].original)
        {
            qtd++;
        }

        cout << contas[i].original + to_string(qtd) << endl;

        i += qtd;
    }
}

int main()
{

    int quant_testes, quant_contas;
    vector<Numero> contas;

    cin >> quant_testes;
    while (quant_testes > 0)
    {

        cin >> quant_contas;

        contas = vector<Numero>(quant_contas);
        cin.ignore();

        for (int i = 0; i < quant_contas; i++)
        {
            getline(cin, contas[i].original);
        }

        radix_counting_sort(contas, quant_contas);

        imprimir_saida(contas, quant_contas);
        cout << endl;

        quant_testes--;
    }
    return 0;
}
