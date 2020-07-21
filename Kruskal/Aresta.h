#ifndef ARESTA_H
#define ARESTA_H
#include <iostream>
#include <vector>
#include <algorithm> // sort
#include <string.h> // memset

using namespace std;

class Aresta
{
    public:
        Aresta();
        virtual ~Aresta();
        Aresta(int v1, int v2, int peso);
        int obterVertice1();
        int obterVertice2();
        int obterPeso();
        bool operator < (const Aresta& aresta2) const //Sobrescrita do operador "<"
        {
            return (peso < aresta2.peso);
        }

    protected:
        int vertice1, vertice2, peso;

    private:
};

#endif // ARESTA_H
