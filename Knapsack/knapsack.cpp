#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <stdio.h>
using namespace std;

int knapsack(int M, int peso[], int valor[], int n)
{
	//Tabela de valores
	//n+1 pois uma linha e uma coluna é inicializada com 0
	int V[n + 1][M + 1];

	//Inicializando a primeira linha e primeira coluna com 0
	for(int w = 0; w <= M; w++){
        V[0][w] = 0;
	}
	for(int i = 1; i <= n; i++){
        V[i][0] = 0;
	}

	//Testando os valores
	for(int i = 1; i <= n; i++)
	{
		for(int w = 1; w <= M; w++)
		{
			// elemento pode fazer parte da solução
			if(peso[i - 1] <= w)
			{
				// max...
				if((valor[i - 1] + V[i - 1][w - peso[i - 1]]) > V[i - 1][w]){
                    V[i][w] = valor[i - 1] + V[i - 1][w - peso[i - 1]];
				}
				else{
                    V[i][w] = V[i - 1][w];
				}
			}
			else{
                V[i][w] = V[i - 1][w];
			}
		}
	}

	//Retorna o valor maximo inserido na mochila
	return V[n][M];
}

int main()
{
	//Numero de elementos
	int n = 0;
	//Capacidade da mochila
	int M = 0;
	//Contador auxiliar
    int cont = 0;

	//Classe de fluxo de entrada para operar em arquivos.
	ifstream arquivo("mochila02.txt", ios::in);

    //Obtem o primerio valor do arquivo
    arquivo >> n;
    //Obtem o segundo valor do arquivo
    arquivo >> M;

    //Vetor de pesos dos objetos
    int peso[n] = {0};
    //Vetor de valor dos objetos
    int valor[n] = {0};

	//Laco para descarregar o arquivo nos vetores
	//Matriz nx2
    for(int i = 0; i < n; i++){
        for(int j = 0; j < 2; j++){
            arquivo >> peso[cont];
            arquivo >> valor[cont];
            cont++;
        }
    }

	//Obtém o máximo valor que pode ser colocado na mochila
	int maximo = knapsack(M, peso, valor, n);

	cout << "Valor maximo obtido eh: " << maximo << endl;

	return 0;
}
