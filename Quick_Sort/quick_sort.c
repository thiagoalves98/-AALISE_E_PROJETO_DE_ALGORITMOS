#include <stdio.h>
#include <stdlib.h>
#define MAX_TAM 10

void Quick_Sort(int vetor[], int inicio, int fim){

	int i, j, pivo, aux;
	i = inicio;
	j = fim-1;
	pivo = vetor[(inicio + fim) / 2];

	while(i <= j){
		while(vetor[i] < pivo && i < fim){
			i++;
		}
		while(vetor[j] > pivo && j > inicio){
			j--;
		}
		if(i <= j){
			aux = vetor[i];
			vetor[i] = vetor[j];
			vetor[j] = aux;
			i++;
			j--;
		}
	}
	if(j > inicio)
		Quick_Sort(vetor, inicio, j+1);
	if(i < fim)
		Quick_Sort(vetor, i, fim);
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

    puts("Vetor Inserido");
    PrintArray(arr, MAX_TAM);
    Quick_Sort(vet, 0, MAX_TAM);
    puts("Vetor Ordenado");
    PrintArray(arr, MAX_TAM);

    return 0;
}