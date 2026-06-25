#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "sequencial.h"

#define NUM_BUSCAS 1000

int busca_sequencial(Registro *array, int tamanho, int id_alvo) {
    for (int i = 0; i < tamanho; i++) {
        if (array[i].id == id_alvo) {
            return i;
        }
    }
    return -1;
}

void medir_desempenho_sequencial(Registro *dados, int tamanho) {
    struct timespec inicio, fim;
    double tempo_total;
    
    int id_inicio = dados[0].id;
    int id_meio = dados[tamanho / 2].id;
    int id_fim = dados[tamanho - 1].id;
    int id_inexistente = -9999;

    int alvos[] = {id_inicio, id_meio, id_fim, id_inexistente};
    char *cenarios[] = {"Inicio", "Meio", "Fim", "Inexistente"};

    printf("--- RESULTADOS BUSCA SEQUENCIAL (FASE I) ---\n");
    printf("Total de registros: %d\n\n", tamanho);

    for (int c = 0; c < 4; c++) {
        clock_gettime(CLOCK_MONOTONIC, &inicio);

        for (int i = 0; i < NUM_BUSCAS; i++) {
            busca_sequencial(dados, tamanho, alvos[c]);
        }

        clock_gettime(CLOCK_MONOTONIC, &fim);

        tempo_total = (fim.tv_sec - inicio.tv_sec) + 
                      (fim.tv_nsec - inicio.tv_nsec) / 1e9;
        
        double tempo_medio = tempo_total / NUM_BUSCAS;

        printf("Cenario: %s (ID: %d)\n", cenarios[c], alvos[c]);
        printf("Tempo medio por busca: %.9f s\n\n", tempo_medio);
    }
}