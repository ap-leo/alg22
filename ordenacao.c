#include "ordenacao.h"
#include "pilha.h"

#include <stdio.h>
#include <stdlib.h>


#include <string.h>

void trocar(int v[], int ini, int fim){
    int aux = v[ini];
    v[ini] = v[fim];
    v[fim] = aux;

    return;
}

int particionar(int v[], int ini, int fim, uint64_t *comp){
    int x = v[fim];
    int m = ini;
    for (int i = ini; i < fim; i++){
        if (v[i] <= x){
             trocar(v, m, i);
             m++;
        }
    (*comp)++;
    }
    trocar(v, m, fim);

    return m;
}

void copiar (int v[], int u[], int ini, int fim){
    int i = 0;
    while (i <= fim - ini){
        v[ini + i] = u[i];
        i++;
    }

    return;
}

void merge (int v[], int ini, int m, int fim, uint64_t *comp){
    if (ini >= fim)
        return;
    int* u = (int*)malloc((fim + 1) * sizeof(int));
    if (u == NULL){
        printf("erro alocacao merge"); 

        return;
    }
    int k = 0;
    int i = ini;
    int j = m + 1;
    int p;
    while (k <= fim - ini){
        (*comp)++;
        if (j > fim || (i <= m && v[i] <= v[j])){
            p = i;
            i++;
        }
        else{
            p = j;
            j++;
        }
        u[k] = v[p];
        k++;
    }

    copiar(v, u, ini, fim);

    return;
}


void quickSortAux(int v[], int ini, int fim, uint64_t* comp){
    if (ini >= fim)
        return;

    int m = particionar(v, ini, fim, comp);
    quickSortAux(v, ini,m - 1, comp);
    quickSortAux(v, m + 1, fim, comp);

    return;
}

void mergeSortAux (int v[], int ini, int fim, uint64_t *comp){
    if (ini >= fim)
        return;
    
    int m = (ini+fim)/2;
    mergeSortAux(v,ini,m, comp);
    mergeSortAux(v,m + 1,fim, comp);
    merge(v,ini,m,fim, comp);
    
    return;
}

int pai(int i){
    return i / 2;
}

int esquerda (int i){
    return i * 2;
}

int direita (int i){
    return i * 2 + 1;
}

void max_heapify(int vetor[], int i, int n, uint64_t *comp){
    int l = esquerda(i);
    int r = direita(i);

    int maior;
    *comp += 2;
    if(l <= n && vetor[l] > vetor[i]){
        maior = l;
    }

    else{
        maior = i;
    }

    if(r <= n && vetor[r] > vetor[maior]){
        maior = r;
    }

    if(maior != i){
        trocar(vetor, i, maior);
        max_heapify(vetor, maior, n, comp);
    }

    return;
}

void max_heapifySR(int vetor[], int i, int n, uint64_t *comp){
    struct pilha *h = pilha_cria();
    if(h == NULL){
        printf("Erro: Falha na alocação da pilha.\n");
        return;
    }

    push(h, i); // Empilha o índice inicial 'i'
    int l, r, maior;

    while(!pilha_vazia(h)){
        pop(h, &i); // Desempilha o índice atual 'i'
        l = esquerda(i);
        r = direita(i);
        maior = i;

        *comp += 2;
        if(l <= n && vetor[l] > vetor[maior]){
            maior = l;
        }

        if(r <= n && vetor[r] > vetor[maior]){
            maior = r;
        }

        if(maior != i){
            trocar(vetor, i, maior);
            push(h, maior); 
        }
    }

    return;
}


void construir_max_heap(int vetor[], int fim, uint64_t *comp, int aux){
    if(aux){
        for (int i = (fim / 2); i >= 0; i--){
            max_heapify(vetor, i, fim, comp);
        }
    }
    else{
        for (int i = (fim / 2); i >= 0; i--){
            max_heapifySR(vetor, i, fim, comp);
        }
    }

    return;
}

void heapSortAux(int vetor[], int inicio, int fim, uint64_t *comp){
    construir_max_heap(vetor, fim, comp, 1);
    for (int i = fim; i > 0; i--){
        trocar(vetor, 0, i);
        max_heapify(vetor, 0, i-1, comp);
    }

    return;
}

void getNome(char nome[]) {
    // substitua por seu nome
    strncpy(nome, "Leonardo Moisés Pires de Alcides", MAX_CHAR);
    // adicionada terminação manual para caso de overflow
    nome[MAX_CHAR - 1] = '\0';
}

// ini função ini seguir deve retornar o seu número de GRR
uint32_t getGRR() { return 20232376; }

uint64_t mergeSort(int v[], size_t tam) {
    uint64_t comp = 0;
    mergeSortAux(v, 0, tam - 1, &comp);
    return comp;
}

uint64_t quickSort(int v[], size_t tam) {
    uint64_t comp = 0;
    quickSortAux(v, 0, tam - 1, &comp);
    return comp;
}

uint64_t heapSort(int v[], size_t tam) {
    uint64_t comp = 0;
    heapSortAux(v, 0, tam - 1, &comp);
    return comp;
}

uint64_t mergeSortSR(int v[], size_t tam) {
    struct pilha *ms = pilha_cria(tam); // Criação da pilha com capacidade igual ao tamanho do array
    if (ms == NULL)
        return -1;

    int a, b, m, aux;
    uint64_t comp = 0;

    push(ms, 0);
    push(ms, tam - 1);

    while (!pilha_vazia(ms)) {
        pop(ms, &b);
        pop(ms, &a);

        if (a < b) {
            m = (a + b) / 2;
            push(ms, a);
            push(ms, m);
            push(ms, m + 1);
            push(ms, b);
            merge(v, a, m, b); // Chamada para mesclar as partes ordenadas
        }
    }

    return comp;
}

uint64_t quickSortSR(int v[], size_t tam) {
    struct pilha *q = pilha_cria();
    if (q == NULL)
        return -1;

    int a = 0;
    int b = tam - 1;
    uint64_t comp = 0;
    push(q, a);
    push(q, b);
    while(!pilha_vazia(q)){
        if(pop(q, &b) && pop(q, &a)){
            if (a < b){
                int m = particionar(v,a,b, &comp);
                push(q,a);
                push(q,m-1);
                push(q,m+1);
                push(q,b);
            }
        }
    }

    return comp;
}

uint64_t heapSortSR(int v[], size_t tam) {
    uint64_t comp = 0;
    construir_max_heap(v, tam - 1, &comp, 0);
    for (int i = tam - 1; i > 0; i--){
        trocar(v, 0, i);
        max_heapifySR(v, 0, i-1, &comp);
    }

    return comp;
}

