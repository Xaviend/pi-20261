#include <stdlib.h>
#include "hash.h"

TabelaHash* criar_hash(int tamanho) {
    TabelaHash *h = malloc(sizeof(TabelaHash));
    h->tamanho = tamanho;
    h->colisoes = 0;
    h->tabela = calloc(tamanho, sizeof(No*));
    return h;
}

void inserir_hash(TabelaHash *h, Registro r) {
    unsigned int indice = (r.id * 31) % h->tamanho;
    No *novo = malloc(sizeof(No));
    novo->dado = r;
    novo->prox = h->tabela[indice];
    
    if (h->tabela[indice] != NULL) {
        h->colisoes++;
    }
    h->tabela[indice] = novo;
}

Registro* buscar_hash(TabelaHash *h, int id) {
    unsigned int indice = (id * 31) % h->tamanho;
    No *atual = h->tabela[indice];
    
    while (atual != NULL) {
        if (atual->dado.id == id) {
            return &(atual->dado);
        }
        atual = atual->prox;
    }
    return NULL;
}

void liberar_hash(TabelaHash *h) {
    for (int i = 0; i < h->tamanho; i++) {
        No *atual = h->tabela[i];
        while (atual != NULL) {
            No *temp = atual;
            atual = atual->prox;
            free(temp);
        }
    }
    free(h->tabela);
    free(h);
}