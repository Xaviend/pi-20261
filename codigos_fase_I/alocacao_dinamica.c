#ifndef PRODUTO_H
#define PRODUTO_H

typedef struct {
    int id;
    char nome[51];
    char categoria[31];
    float valor;
} Produto;

#endif

#include <stdio.h>
#include <stdlib.h>
#include "Produto.h"

Produto* criarVetor(int tamanho) {
    // Aloca um bloco contíguo de memória para 'tamanho' produtos
    Produto* vetor = (Produto*) malloc(tamanho * sizeof(Produto));
    
    if (vetor == NULL) {
        fprintf(stderr, "Erro: Falha Crítica de Memória!\n");
        exit(1);
    }
    return vetor;
}

void liberarVetor(Produto* vetor) {
    free(vetor);
}