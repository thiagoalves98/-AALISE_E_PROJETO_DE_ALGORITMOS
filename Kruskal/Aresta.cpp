#include "Aresta.h"

Aresta::Aresta()
{
    //ctor
}

Aresta::~Aresta()
{
    //dtor
}

Aresta::Aresta(int v1, int v2, int peso) //Cria um objeto aresta
{
    vertice1 = v1;
    vertice2 = v2;
    this->peso = peso;
}

Aresta::obterVertice1() //Retorna o vertice inicial da aresta
{
    return vertice1;
}

Aresta::obterVertice2() //Retorna o vertice final da aresta
{
    return vertice2;
}

Aresta::obterPeso() //Obtem o peso da aresta
{
    return peso;
}

