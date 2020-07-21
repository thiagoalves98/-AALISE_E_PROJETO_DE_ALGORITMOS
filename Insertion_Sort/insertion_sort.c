#include <stdio.h>
#include <stdlib.h>

void Insertion_Sort(int arr[], int tam){

  int i, j, key;

  for (i = 1; i < tam; i++){
    key = arr[i];
    j = i-1;

    while (j >= 0 && arr[j] > key){
      arr[j+1] = arr[j];
      j = j-1;
    }
    arr[j+1] = key;
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
  Insertion_Sort(arr1, tam);
  puts("Vetor ordenado: ");
  PrintArray(arr1, tam);

  return 0;
}