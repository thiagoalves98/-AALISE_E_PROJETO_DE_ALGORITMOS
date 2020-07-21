#include <stdio.h>
#include <stdlib.h>
#define MAX_TAM 10

void Couting_Sort(int A[], int k, int tamanho){

    int C[k+1];
    int B[tamanho];

    for(int i = 0; i <= k; i++){    //zera o vetor auxiliar
        C[i] = 0;
    }

    for(int j = 0; j < tamanho; j++){   //incrementa 1 para cada valor igual encontrado no array inicial
        C[A[j]] = C[A[j]] + 1;
    }

    for(int i = 1; i <= k; i++){    //soma com o anterior
        C[i] = C[i] + C[i-1];
    }

    for(int j = (tamanho-1); j >= 0; j--){  //posiciona o valor no array ordenado
        B[C[A[j]]- 1 ] = A[j];
        C[A[j]] = C[A[j]] - 1;
    }

    puts("\n\nVetor Ordenado");
    PrintArray(arr, tamanho);
}

void PrintArray(int arr[], int n){

  for (int i=0; i < n; i++)
    printf("%d ", arr[i]);
  printf("\n");
}

int main(){

    int arr[MAX_TAM];
    int k = 0;

    puts("Preenchendo o vetor...");
    for(int i=0; i < MAX_TAM; i++){
        printf("Digite o valor a ser inserido na posicao [%i]", i);
        scanf("%i", &arr[i]);
        if (k < arr[i]){
            k = arr[i];
        }
    }

    puts("\nVetor Inserido: ");
    PrintArray(arr, MAX_TAM);
    printf("\nIntervalo: k = [0, %i]", k);
    Couting_Sort(arr, k, MAX_TAM);

    return 0;
}