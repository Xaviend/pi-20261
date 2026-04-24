#include "produto.h"

int buscaSequencial(int id, Produto *vetor, int tamanho) {
    for (int i = 0; i < tamanho; i++) {
        if (vetor[i].id == id) {
            return i; // Retorna o índice
        }
    }
    return -1; // Não encontrado
}