#include <stdio.h>
#include <stdlib.h>
#define MAX_TAM 10

void MaxHeapify(int A[], int tamanho_heap, int i){
    
    int L = 2*i +1; //filho da esquerda
    int R = 2*i +2; //filho da direita
    int maior = i;
    int aux;

    if(L < tamanho_heap && A[L] > A[maior]){
        maior = L;
    }
    if(R < tamanho_heap && A[R] > A[maior]){
        maior = R;
    }
    if(maior != i){
        aux = A[i]; //troca( )
        A[i] = A[maior];
        A[maior] = aux;
        MaxHeapify(A, i, maior);
    }
}

void BuildMaxHeap(int A[], int tamanho_heap){

    int comprimentoA = tamanho_heap;

    for(int i = (comprimentoA/2)-1; i >= 0; i--){
        MaxHeapify(A, tamanho_heap, i);
    }
}

void Heap_Sort(int A[], int tamanho_heap){

    int aux = 0;

    BuildMaxHeap(A, tamanho_heap);

    for(int i = tamanho_heap-1; i >= 0; i--){
        aux = A[0];
        A[0] = A[i];
        A[i] = aux;
        MaxHeapify(A, i, 0);
    }

    puts("\n\nVetor Ordenado");
    PrintArray(arr, tamanho_heap);
}

void PrintArray(int arr[], int n){

  for (int i=0; i < n; i++)
    printf("%d ", arr[i]);
  printf("\n");
}

int main(){

    int arr[MAX_TAM];

    puts("Preenchendo o vetor...");
    for(int i=0; i < MAX_TAM; i++){
        printf("Digite o valor a ser inserido na posicao [%i]", i);
        scanf("%i", &arr[i]);
    }

    puts("\nVetor Inserido:");
    PrintArray(arr, MAX_TAM);
    Heap_Sort(vet, MAX_TAM);

    return 0;
}