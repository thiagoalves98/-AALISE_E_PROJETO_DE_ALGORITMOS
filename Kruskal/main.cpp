#include <iostream>
#include <fstream>
#include <vector>
#include <stdlib.h>
#include <stdio.h>
#include <algorithm> // sort
#include <string.h> // memset
#include "Grafo.h"
#include "Aresta.h"

using namespace std;

int main()
{
    int tamanho;

    //Classe de fluxo de entrada para operar em arquivos.
	ifstream arquivo("dij10.txt", ios::in);

    //Obtem o primerio valor do arquivo
    arquivo >> tamanho;

    //Inicia uma matriz tamamnhoXtamanho com 0
    int matriz[tamanho][tamanho] = {0};

    //Chama o construtor do grafo e cria um grafo de tamanho indicado pelo primeiro valor do arquivo
    Grafo g(tamanho);

    //Laco para descarregar o arquivo na matriz
    for(int i = 0; i < tamanho; i++){
        for(int j = i; j < tamanho; j++){
            if(i == j){
                continue;
            }
            //Insere um proximo valor do arquvio na matriz
            arquivo >> matriz[i][j];
        }
    }
    //Laco para inserir os valores do grafo
    for(int i = 0; i < tamanho; i++){
        for(int j = i; j < tamanho; j++){
            if(i == j){
                continue;
            }
            //Vertice inicial,vertice final e peso da aresta que conecta elas
            g.adicionarAresta(i, j, matriz[i][j]);
        }
    }
    //Inicia o algoritmo de kruskal
	g.kruskal();

	return 0;
}
