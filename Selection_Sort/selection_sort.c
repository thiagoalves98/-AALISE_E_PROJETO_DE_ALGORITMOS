#include <stdio.h>
#include <stdlib.h>

void Selection_Sort(int arr[], int tam){

  int i, j, min, aux;
  for (i = 0; i < (tam-1); i++)
  {
     min = i;
     for (j = (i+1); j < tam; j++) {
       if(arr[j] < arr[min])
         min = j;
     }
     if (arr[i] != arr[min]) {
       aux = arr[i];
       arr[i] = arr[min];
       arr[min] = aux;
     }
  }
}

void PrintArray(int arr[], int n){

  for (int i=0; i < n; i++)
    printf("%d ", arr[i]);
  printf("\n");
}

int main(){

  int arr1[] = {5, 4, 3, 2, 1}; //pior caso
  int arr2[] = {1, 2, 5, 4, 3}; //caso intermediario
  int arr3[] = {1, 2, 3, 4, 5}; //melhor caso

  int tam = sizeof(arr1)/sizeof(arr1[0]);

  puts("Vetor nao ordenado: ");
  PrintArray(arr1, tam);
  Selection_Sort(arr1, tam);
  puts("Vetor ordenado: ");
  PrintArray(arr1, tam);

  return 0;
}