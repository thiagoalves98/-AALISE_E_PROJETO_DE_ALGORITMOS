#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <time.h>
#include "Vertice.h"
#define MAX_CORES 60

using namespace std;

const int Cores[MAX_CORES] = {  60, 59, 58, 57, 56, 55, 54, 53, 52, 51,
                                50, 49, 48, 47, 46, 45, 44, 43, 42, 41,
                                40, 39, 38, 37, 36, 35, 34, 33, 32, 31,
                                30, 29, 28, 27, 26, 25, 24, 23, 22, 21,
                                20, 19, 18, 17, 16, 15, 14, 13, 12, 11,
                                10,  9,  8,  7,  6,  5,  4,  3,  2,  1};

vector<vector<Vertice>>Bucket(MAX_CORES);

vector <Vertice> vertices;

int nVertices = 0;  //Numero de vertices do grafo

int CoresGulosas = 0;   //Contador de cores ultilizadas;
int CoresDSATUR = 0;

/*Funcoes*/
void SaturaVizinhanca(vector <int> vizinhos, int nVizinhos);
void ColoracaoGulosa(int nVertices);
void PreencheBucket(int nVertices);
void EsvaziaBucket(int nVertices);
void SortVertices(int nVertices);
void ZeraCores(int nVertices);
void DSATUR(int nVertices);
int MovimentaBucket(int IndexBucket, int QuantidadeCores);
int GRASP(int nVertices, float percent, int nLoop);
int VerificaMaiorSaturacao(int nVertices);
int CoresUltilizadas(int nVertices);
int FlagColoridos(int nVertices);
int ColorirVertice(int v);

void SaturaVizinhanca(vector <int> vizinhos, int nVizinhos)
{
    int aux, aux2, CorDoVizinho,  saturacao;
    int Corsetada[MAX_CORES] = {};
    int Contador = 0;

    for(int i = 0; i < nVizinhos; i++){
        //Pega o grau do primeiro vizinho
        aux = vertices[vizinhos[i]].ObtemGrauDoVertice();

        //Olha pra todos os vizinhos do vizinho analizado e seta -1 as cores ultilizadas por eles
        for(int j = 0; j < aux; j++){
            //Obtem o vizinho j do vizinho i
            aux2 = vertices[vizinhos[i]].ObtemVizinho(j);

            for(int k = 0; k < nVertices+1; k++){
                if(vertices[k].ObtemID() == aux2){
                    CorDoVizinho = vertices[k].ObtemCor();
                    break;
                }
            }

            for(int k = 0; k < MAX_CORES; k++){
                if(CorDoVizinho == Cores[k]){
                    Corsetada[k] = -1;
                    break;
                }
            }
        }

        for(int j = 0; j < MAX_CORES; j++){
            if(Corsetada[j] == -1){
                //Contabiliza a cor encontrada
                Contador++;
                //Zera a posição para o proximo vizinho ultilizar
                Corsetada[j] = 0;
            }
        }

        saturacao = MAX_CORES-Contador;
        vertices[vizinhos[i]].MudaSaturacao(saturacao);
        Contador = 0;
    }
}

int FlagColoridos(int nVertices)
{
    for(int i = 0; i < nVertices+1; i++){
        if(vertices[i].ObtemFlag() == 0){
            //Retorna 1 para informar que o processo deve continuar
            return 1;
        }
    }
    //Caso nao encontre nenhum vertice para ser colorido, retorna 0 para informar que o processo deve parar
    //printf("\nTodo o grafo foi colorido!\n\n");
    return 0;
}

int VerificaMaiorSaturacao(int nVertices)
{
    int VerticesSetados[nVertices+1] = {};
    int Saturacoes[nVertices+1] = {};
    int contador = 0;

    //Analiza os vertices nao setados
    for(int i = 0; i < nVertices+1; i++){
        if(vertices[i].ObtemFlag() == 0){
            //Puxa o indice do vertice nao setado
            VerticesSetados[i] = 1;
            contador++;
        }
    }

    for(int i = 0; i < nVertices+1; i++){
        if(VerticesSetados[i] == 1){
           Saturacoes[i] = vertices[i].ObtemSaturacao();
        }
    }

    int minimo = 1000000;
    int minIndex = 0;
    for(int i = 0; i <= nVertices; i++){
        if(Saturacoes[i] > 0 && Saturacoes[i] < minimo){
                minimo = Saturacoes[i];
                minIndex = i;
        }
    }

    return minIndex;
}

void SortVertices(int nVertices)
{
    for(int i = 0; i < nVertices+1; i++){
        for(int j = 0; j < nVertices; j++){
            if(vertices[j+1].ObtemGrauDoVertice() > vertices[j].ObtemGrauDoVertice()){
                swap(vertices[j+1], vertices[j]);
            }
        }
    }
}

int ColorirVertice(int v)
{
    vector <int> VerticesVizinhos;
    int nVizinhos = vertices[v].ObtemGrauDoVertice();
    int aux = 0;
    int CorDoVizinho;
    int CoresDisponiveis[MAX_CORES] = {};
    int CorSetada = 0;

    for(int i = 0; i < nVizinhos; i++){

        aux = vertices[v].ObtemVizinho(i);

        for(int k = 0; k < nVertices+1; k++){
            if(vertices[k].ObtemID() == aux){
                VerticesVizinhos.push_back(k);
                CorDoVizinho = vertices[k].ObtemCor();
                break;
            }
        }

        for(int j = 0; j < MAX_CORES; j++){
            if(CorDoVizinho == Cores[j]){
                CoresDisponiveis[j] = -1;
            }
        }
    }

    for(int i = 0; i < MAX_CORES; i++){
        if(CoresDisponiveis[i] == -1){
            CorSetada++;
        }
    }

    if(CorSetada == MAX_CORES){
        //printf("\nVertice [%d] de ID [%d] nao pode ser Colorido!\n", v, vertices[v].ObtemID());
        //printf("Todas as cores foram utilizadas!\n\n");
        return -1;
    }

    //Varre o array com as cores setadas. A primeira cor encontrada diferente de -1 é inserida no vertice
    for(int i = 0; i < MAX_CORES; i++){
        if(CoresDisponiveis[i] != -1){

            vertices[v].MudaCor(Cores[i]);                        //Insere a cor

            vertices[v].MudaFlag(1);                             //Sinaliza que foi colorido

            vertices[v].MudaSaturacao(MAX_CORES-CorSetada);      //Atualiza a saturacao do vertice

            //printf("O vertice %d de ID %d foi colorido\n", v, vertices[v].ObtemID());
            break;
        }
    }

    SaturaVizinhanca(VerticesVizinhos, nVizinhos);      //Como o vertice foi colorido, todos os vertices em volta dele não podem receber a mesma cor.
                                                        // Logo, a saturacao(numero de cores disponiveis) dos vertices vizinhos deve ser decrementado
    return 0;

}

void DSATUR(int nVertices)
{
    int aux;
    int flag = 1;

    SortVertices(nVertices);                     //1ª passo - Ordenar os vertices por ordem Decrescente de grau de adjacencia

    ColorirVertice(0);                           //2ª passo - Colorir o vertice de maior grau com a primeira cor, ou seja, o primeiro vertice do array de vetores apos o sort

    while(flag){                                //3ª passo - Selecione o vértice com maior grau de saturação, ou seja, seleciona o vertice com menos opcoes de cores.
                                                //Repetir o processo enquanto houver vertices para serem coloridos
       aux =  VerificaMaiorSaturacao(nVertices);
       ColorirVertice(aux);
       flag = FlagColoridos(nVertices);
    }
    CoresDSATUR = CoresUltilizadas(nVertices);
    printf("A coloracao com DSATUR utilizou %d cores para colorir todo o grafo!\n\n", CoresDSATUR);
}

void ColoracaoGulosa(int nVertices)
{
    //Ordena os vertices em ordem decrescente de adjacencias e vai colorindo sequencialmente
    SortVertices(nVertices);

    for(int i = 0; i < nVertices; i++){
        ColorirVertice(i);
    }
    CoresGulosas = CoresUltilizadas(nVertices);
    printf("A coloracao gulosa utilizou %d cores para colorir todo o grafo!\n\n", CoresGulosas);
}

int MovimentaBucket(int IndexBucket, int QuantidadeCores)
{
    vector <int> VerticesVizinhos;
    int tam = Bucket[IndexBucket].size();
    int CoresDisponiveis[QuantidadeCores] = {};
    int nVizinhos;
    int aux2, aux = 0;
    int CorDoVizinho;
    int CorSetada = 0;

    if(tam == 0){
        //printf("\nNao possui vertices\n");
        return 0;
    }

    for(int i = 0; i < tam; i++){

        nVizinhos = Bucket[IndexBucket][i].ObtemGrauDoVertice();

        for(int j = 0; j < nVizinhos; j++){

            aux = Bucket[IndexBucket][i].ObtemVizinho(j);       //Obtem o vizinho  do vertice analizado

            for(int k = 0; k < nVertices+1; k++){               //Obtem a cor do vizinho do vertice analizado
                if(vertices[k].ObtemID() == aux){
                    VerticesVizinhos.push_back(k);
                    CorDoVizinho = vertices[k].ObtemCor();
                    break;
                }
            }


            for(int l = 0; l < QuantidadeCores; l++){           //Varre o array de cores e coloca -1 pra cor encontrada
                if(CorDoVizinho == Cores[l]){
                    CoresDisponiveis[l] = -1;
                }
            }
        }



        for(int m = 0; m < QuantidadeCores; m++){                  //Varre o array com as cores setadas. Se todo mundo for -1, nao ha cores disponives para o vertice
            if(CoresDisponiveis[m] == -1){
                CorSetada++;                                       //Conta quantas cores estão indisponiveis
            }
        }

        if(CorSetada+1 == QuantidadeCores){
           // printf("\nA cor do Vertice [%d] do Bucket [%d] nao pode ser trocada!\n", i, IndexBucket);
        }

        for(int p = 0; p < QuantidadeCores; p++){                   //Varre o array com as cores setadas. A primeira cor encontrada diferente de -1 e que não seja a cor dele mesmo é inserida no vertice

            aux2  = Bucket[IndexBucket][i].ObtemCor();

            if((CoresDisponiveis[p] != -1)&&(aux2 != Cores[p])){

                Bucket[IndexBucket][i].MudaCor(Cores[p]);           //Insere a cor e atualiza a saturacao do vertice

                Bucket[IndexBucket][i].MudaSaturacao(QuantidadeCores-CorSetada);

               // printf("\nVertice [%d] do Bucket [%d] foi Recolorido!\n", i, IndexBucket);
                break;
            }
        }

        SaturaVizinhanca(VerticesVizinhos, nVizinhos);

        CorSetada = 0;

    }

    if(Bucket[IndexBucket].size() == 0){
        printf("O Bucket [%d] foi esvaziado com sucesso!\n\n", IndexBucket);
    }

    return 0;
}

void PreencheBucket(int nVertices)
{
    int aux;
    for(int i = 0; i < MAX_CORES; i++){

        for(int j = 0; j < nVertices+1; j++){

            if(vertices[j].ObtemCor() == Cores[i]){
                Bucket[i].push_back(vertices[j]);
            }
        }
    }
    /*
    for(int i = 0; i < Bucket.size(); i++){
        printf("Bucket[%d]\n", i);
        aux = Bucket[i].size();
        for(int j = 0; j < aux; j++){
            printf("[%d] ", Bucket[i][j].ObtemID());
        }
        puts("\n");
    }*/
}

int CoresUltilizadas(int nVertices)
{
    vector <int> CoresUtilizadas;
    int contador = 0;

    for(int i = 0; i < MAX_CORES; i++){
        for(int j = 0; j < nVertices+1; j++){
            if(vertices[j].ObtemCor() == Cores[i]){
                contador++;
            }
        }
        if(contador != 0){
            CoresUtilizadas.push_back(contador);
            contador = 0;
        }
    }

    return CoresUtilizadas.size();
}

void ZeraCores(int nVertices)
{
    for(int i = 0; i < nVertices+1; i++){
        vertices[i].MudaCor(-1);
        vertices[i].MudaFlag(0);
        vertices[i].MudaSaturacao(MAX_CORES);
    }
}

void EsvaziaBucket(int nVertices)
{
    int tam = CoresUltilizadas(nVertices);

    for(int i = 0; i < tam; i++){
        for(int j = 0; j < Bucket[i].size(); j++){
             Bucket.erase(Bucket.begin());
        }
    }
}

int GRASP(int nVertices, float percent, int nLoop)
{
    vector <Vertice> SubConjunto;
    int alfa = (nVertices+1)*(percent/100);
    int random;
    int quantidade = 0;
    int SolucaoConstrutiva;
    int MelhorResultado;
    srand((unsigned) time(NULL));

    for(int i = 0; i < nLoop; i++){

        ZeraCores(nVertices);                   //Limpa as cores para que o grafo possa ser colorido novamente

        EsvaziaBucket(nVertices);                //Esvazia soluçao anterior

        for(int i = 0; i < nVertices+1; i++){       //Faz uma copia do grafo
            SubConjunto.push_back(vertices[i]);

        }

        while(FlagColoridos(nVertices)){                        //Retorna 1 enquanto faltar vertices para serem coloridos

            //alfa = (SubConjunto.size())*(percent/100);          //Pega X porcento do tamanho atual do grafo

            random = (rand() % (alfa));                         //Gera um numero aleaforio dentro desde intervalo

            if(vertices[random].ObtemFlag() == 1){
                continue;
            }

            ColorirVertice(random);

            //SubConjunto.erase(SubConjunto.begin()+random);
        }

        //puts("");

        //Preenche com as novas cores dos vertices
        PreencheBucket(nVertices);

        quantidade = CoresUltilizadas(nVertices);

        for(int i = 0; i < quantidade; i++){
            //printf("Bucket [%d]\n", i);
            MovimentaBucket(i, quantidade);
            //puts("");
        }

        if(i == 0){
            SolucaoConstrutiva = CoresUltilizadas(nVertices);
            MelhorResultado = SolucaoConstrutiva;
            printf("\nA SolucaoConstrutiva na [%d] interacao foi %d cores\n", i, MelhorResultado);
            printf("O MelhorResultado parc na [%d] interacao foi %d cores\n", i, MelhorResultado);
        }else{
             SolucaoConstrutiva = CoresUltilizadas(nVertices);
        }

        if(SolucaoConstrutiva < MelhorResultado){
            MelhorResultado = SolucaoConstrutiva;

        }
        printf("\nA SolucaoConstrutiva na [%d] interacao foi %d cores\n", i, SolucaoConstrutiva);
        printf("O MelhorResultado parc na [%d] interacao foi %d cores\n", i, MelhorResultado);
    }

    return MelhorResultado;
}

int main()
{
    //Define o problema
    string p;
    //
    string edge;
	//Numero de Arestas
	int nArestas = 0;
	//Indica uma aresta
	string e;
	//vertice origem
	int n1;
	//Vertice destino
	int n2;

	//Classe de fluxo de entrada para operar em arquivos.
	ifstream arquivo("instancia3.txt", ios::in);

    //Lendo a primera linha do arquivo
    arquivo >> p;
    arquivo >> edge;
    arquivo >> nVertices;
    arquivo >> nArestas;

    //Matriz de adjacencia com tamanho nVertices+1 e inciada com 0
    int matrizAdj[451][451] = {};

    //Lendo as demais linhas e preenchendo a matriz de adjacencia
    for(int i = 0; i < nArestas; i++){
        arquivo >> e;
        arquivo >> n1;
        arquivo >> n2;
        matrizAdj[n1][n2] = 1;
        matrizAdj[n2][n1] = 1;
    }

    //Contador. Armazena a quantidade de vertices adjacentes cada vertice tem
    int grau = 0;

    //Laço para percorrer a matriz de adjacencia
    for(int i = 0; i < nVertices+1; i++){
        vector <int> VerticesAdj;
        //Percorre as colunas da linha i
        for(int j = 0; j < nVertices+1; j++){
            //Se valor diferente de zero, existe aresta
            if(matrizAdj[i][j] != 0){
                //Contabiliza a aresta encontrada
                grau++;
                //Adiciona no array o indice da aresta encontrada
                VerticesAdj.push_back(j);
            }
        }
        //Constroi o vertice com as informacoes obtidas
        Vertice vertice(VerticesAdj, grau, -1, i, MAX_CORES, 0);
        //Adiciona o novo vertice criado ao array de vertices do grafo
        vertices.push_back(vertice);
        //Zera o contador para o proximo vertice ultilizar
        grau = 0;
    }

    printf("Coloracao Gulosa\n");

    ColoracaoGulosa(nVertices);

    ZeraCores(nVertices);

    printf("Dsatur\n");

    DSATUR(nVertices);

    printf("DSATUR encerrado. Iniciando a movimentacao...\n\n");

    PreencheBucket(nVertices);

    int tamanhoBuck = Bucket.size();

    for(int i = 0; i < tamanhoBuck; i++){
        //printf("Bucket [%d]\n", i);
        MovimentaBucket(i, CoresDSATUR);
        //puts("");
    }

    printf("Zerando cores para nova coloracao\n\n");

    ZeraCores(nVertices);

    float alfa = 100; //Porcento

    printf("Iniciando o GRASP\n\n");

    int Melhor = GRASP(nVertices, alfa, 15);

    puts("\n***Resultados Finais***\n");
    printf("Melhor resultado com o Guloso foi %d\n", CoresGulosas);
    printf("Melhor resultado com o DSatur foi %d\n", CoresDSATUR);
    printf("Melhor resultado com o Grasp  foi %d\n", Melhor);

	return 0;
}
