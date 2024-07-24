#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include "ordenacao.h"
#include "pilha.h"


void imprimir(int v[], int tam){
    for (int i = 0; i < tam; ++i)
    {
        printf("%d ", v[i]);
    }
    printf("\n");

    return;
}

void criarVetor(int vetor[], int tam){
    for(int i = 0; i < tam; i++){
        vetor[i] = rand() % 50;
    }

    return;
}


int main() {
    srand(0);
    //char nome[MAX_CHAR];
    int numComp;

    int tamVetor = 10;
    int* vetor = (int*)malloc(tamVetor * sizeof(int));
    if (vetor == NULL) {
        printf("Falha fatal. Impossível alocar memoria.");
        return 1;
    }

    /* getNome(nome);
    printf("Trabalho de %s\n", nome);
    printf("GRR %u\n", getGRR()); */
    criarVetor(vetor, tamVetor);
    numComp = mergeSort(vetor, tamVetor);
    printf("\n\nmergeSort NumComp: %d\n", numComp);
    imprimir(vetor, tamVetor);

    criarVetor(vetor, tamVetor);
    numComp = quickSort(vetor, tamVetor);
    printf("\n\nquickSort NumComp: %d\n", numComp);
    imprimir(vetor, tamVetor);

    criarVetor(vetor, tamVetor);
    numComp = heapSort(vetor, tamVetor);
    printf("\n\nheapSort NumComp: %d\n", numComp);
    imprimir(vetor, tamVetor);

    criarVetor(vetor, tamVetor);
    numComp = quickSortSR(vetor, tamVetor);
    printf("\n\nquickSortSR NumComp: %d\n", numComp);
    imprimir(vetor, tamVetor);

    criarVetor(vetor, tamVetor);
    numComp = heapSortSR(vetor, tamVetor);
    printf("\n\nheapSortSR NumComp: %d\n", numComp);
    imprimir(vetor, tamVetor);

    criarVetor(vetor, tamVetor);
    numComp = mergeSortSR(vetor, tamVetor);
    printf("\n\nmergeSortSR NumComp: %d\n", numComp);
    imprimir(vetor, tamVetor);

    free(vetor);

    return 0;
}
