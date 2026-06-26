#ifndef HASH_H
#define HASH_H
#include "estrutura.h"

typedef struct No {
    Registro dado;
    struct No *prox;
} No;

typedef struct {
    No **tabela;
    int tamanho;
    int colisoes;
} TabelaHash;

TabelaHash* criar_hash(int tamanho);
void inserir_hash(TabelaHash *h, Registro r);
Registro* buscar_hash(TabelaHash *h, int id);
void liberar_hash(TabelaHash *h);

#endif