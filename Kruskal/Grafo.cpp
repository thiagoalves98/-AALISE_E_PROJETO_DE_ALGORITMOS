#include "Grafo.h"

Grafo::Grafo()
{
    //ctor
}

Grafo::~Grafo()
{
    //dtor
}

Grafo::Grafo(int V) //Construtor do grafo N
{
    this->V = V;
}

Grafo::adicionarAresta(int v1, int v2, int peso) //Função que adiciona as vertices e a aresta
{
    //Chama o contrutor e cria um objeto aresta
    Aresta aresta(v1, v2, peso);
    //Adiciona a nova aresta ao vector de arestas
    arestas.push_back(aresta);
}

Grafo::buscar(int subset[], int i) //Função que busca o subconjunto de um elemento "i"
{
    if(subset[i] == -1){
        return i;
    }
    return buscar(subset, subset[i]);
}

Grafo::unir(int subset[], int v1, int v2) //Função para unir dois subconjuntos em um único subconjunto
{
    int v1_set = buscar(subset, v1);
    int v2_set = buscar(subset, v2);
    subset[v1_set] = v2_set;
}

Grafo::kruskal() //Algoritmo de Kruskal
{
    //Cria um vector para a srvore geradora minima
    vector<Aresta> arvore;

    //Retorna o numero de elementos no vector arvore
    int size_arestas = arestas.size();

    //Ordena todas as arestas pelo menor peso
    sort(arestas.begin(), arestas.end());

    //Aloca "V" espaços de memória para o tamanho inteiro
    int * subset = new int[V];

    //Inicializa todos os subconjuntos como -1
    memset(subset, -1, sizeof(int) * V);

    //Busca as arestas
    for(int i = 0; i < size_arestas; i++){

        int v1 = buscar(subset, arestas[i].obterVertice1());

        int v2 = buscar(subset, arestas[i].obterVertice2());

        if(v1 != v2){
            //Se forem diferentes é porque NÃO forma ciclo, logo, podemos inserir na arvore
            arvore.push_back(arestas[i]);
            // faz a união
            unir(subset, v1, v2);
        }
    }

    //Obtem o tamanho final da arvore
    int size_arvore = arvore.size();

    //Mostra as arestas selecionadas com seus respectivos pesos
    for(int i = 0; i < size_arvore; i++){
            int v1 = arvore[i].obterVertice1();
			int v2 = arvore[i].obterVertice2();
			cout << "(" << v1 << ", " << v2 << ") = " << arvore[i].obterPeso() << endl;
    }
}
