#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "dataset.h"
#include "hash.h"
#include "sequencial.h"

double tempo_decorrido(struct timespec inicio, struct timespec fim) {
    return (fim.tv_sec - inicio.tv_sec) + (fim.tv_nsec - inicio.tv_nsec) / 1e9;
}

int main() {
    Registro *dados = NULL;
    int total_registros = carregar_dataset("dataset3.csv", &dados);
    if (total_registros == 0) return 1;

    TabelaHash *h = criar_hash(total_registros);
    for (int i = 0; i < total_registros; i++) {
        inserir_hash(h, dados[i]);
    }

    int ids_teste[4] = {
        dados[0].id,
        dados[total_registros / 2].id,
        dados[total_registros - 1].id,
        -1
    };

    printf("Total de registros: %d\n", total_registros);
    printf("Colisoes na Tabela Hash: %d\n\n", h->colisoes);

    for (int c = 0; c < 4; c++) {
        int id_alvo = ids_teste[c];
        printf("--- Testando ID: %d ---\n", id_alvo);

        double tempo_hash_total = 0;
        for (int rep = 0; rep < 3; rep++) {
            struct timespec inicio, fim;
            clock_gettime(CLOCK_MONOTONIC, &inicio);
            for (int i = 0; i < 1000; i++) {
                buscar_hash(h, id_alvo);
            }
            clock_gettime(CLOCK_MONOTONIC, &fim);
            tempo_hash_total += tempo_decorrido(inicio, fim);
        }
        printf("Hash - Tempo Total (3 reps): %f s | Medio por busca: %f s\n", tempo_hash_total, tempo_hash_total / 3000.0);

        double tempo_seq_total = 0;
        for (int rep = 0; rep < 3; rep++) {
            struct timespec inicio, fim;
            clock_gettime(CLOCK_MONOTONIC, &inicio);
            for (int i = 0; i < 1000; i++) {
                busca_sequencial(dados, total_registros, id_alvo);
            }
            clock_gettime(CLOCK_MONOTONIC, &fim);
            tempo_seq_total += tempo_decorrido(inicio, fim);
        }
        printf("Seq  - Tempo Total (3 reps): %f s | Medio por busca: %f s\n\n", tempo_seq_total, tempo_seq_total / 3000.0);
    }

    liberar_hash(h);
    free(dados);
    return 0;
}