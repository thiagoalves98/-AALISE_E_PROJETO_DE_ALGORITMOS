#include <stdio.h>
#include <stdlib.h>
#define MAX_TAM 10

void Merge(int vetor[], int inicio, int meio, int fim){

    int com1 = inicio, com2 = meio+1, comAux = 0, tam = fim-inicio+1;
    int *vetAux;
    vetAux = (int*)malloc(tam * sizeof(int));

    while(com1 <= meio && com2 <= fim){
        if(vetor[com1] < vetor[com2]){
            vetAux[comAux] = vetor[com1];
            com1++;
        }else{
            vetAux[comAux] = vetor[com2];
            com2++;
        }
        comAux++;
    }

    while(com1 <= meio){    //Caso ainda haja elementos na primeira metade
        vetAux[comAux] = vetor[com1];
        comAux++;
        com1++;
    }

    while(com2 <= fim) {    //Caso ainda haja elementos na segunda metade
        vetAux[comAux] = vetor[com2];
        comAux++;
        com2++;
    }

    for(comAux = inicio; comAux <= fim; comAux++){  //Move os elementos de volta para o vetor original
        vetor[comAux] = vetAux[comAux-inicio];
    }

    free(vetAux);
}

void Merge_Sort(int vetor[], int inicio, int fim){

    if (inicio < fim){
        int meio = ((fim-1)+inicio)/2;
        Merge_Sort(vetor, inicio, meio);
        Merge_Sort(vetor, meio+1, fim);
        Merge(vetor, inicio, meio, fim);
    }
}

void PrintArray(int arr[], int n){

  for (int i=0; i < n; i++)
    printf("%d ", arr[i]);
  printf("\n");
}

int main(){

    int vet[MAX_TAM];
    puts("Preenchendo o vetor...");

    for(int i=0; i < MAX_TAM; i++){
        printf("Digite o valor a ser inserido na posicao [%i]", i);
        scanf("%i", &vet[i]);
    }

    puts("Vetor Inserido");
    PrintArray(arr, MAX_TAM);
    Merge_Sort(vet, 0, MAX_TAM);
    puts("Vetor Ordenado");
    PrintArray(arr, MAX_TAM);

    return 0;
}