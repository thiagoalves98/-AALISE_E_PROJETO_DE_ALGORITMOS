#ifndef GRAFO_H
#define GRAFO_H
#include <iostream>
#include <vector>
#include <algorithm> // sort
#include <string.h> // memset
#include "Aresta.h"

using namespace std;

class Grafo
{
    public:
        Grafo();
        virtual ~Grafo();
        Grafo(int);
        int adicionarAresta(int v1, int v2, int peso);
        int buscar(int subset[], int i);
        int unir(int subset[], int v1, int v2);
        int kruskal();

    protected:
        //Valor que indica o tamanho do grafo (numero de vertices)
        int V;
        //Vetor de arestas
        vector<Aresta> arestas;

    private:
};

#endif // GRAFO_H
