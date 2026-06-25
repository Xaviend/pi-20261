#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dataset.h"

#define CAPACIDADE_INICIAL 1000
#define TAMANHO_LINHA 256

Registro* carregar_dados(const char *caminho_arquivo, int *tamanho_saida) {
    FILE *file = fopen(caminho_arquivo, "r");
    if (!file) {
        fprintf(stderr, "[ERRO FATAL] O dataset '%s' nao foi encontrado.\n", caminho_arquivo);
        exit(EXIT_FAILURE);
    }

    int capacidade = CAPACIDADE_INICIAL;
    int cont = 0;
    
    Registro *dados = (Registro*) calloc(capacidade, sizeof(Registro));
    if (!dados) {
        fprintf(stderr, "[ERRO FATAL] Falha de alocacao.\n");
        exit(EXIT_FAILURE);
    }

    char linha[TAMANHO_LINHA];
    fgets(linha, TAMANHO_LINHA, file); 

    while (fgets(linha, TAMANHO_LINHA, file)) {
        if (cont >= capacidade) {
            capacidade *= 2;
            Registro *temp = (Registro*) realloc(dados, capacidade * sizeof(Registro));
            if (!temp) {
                fprintf(stderr, "[ERRO FATAL] Estouro de memoria.\n");
                free(dados);
                fclose(file);
                exit(EXIT_FAILURE);
            }
            dados = temp;
        }

        char *token_id = strtok(linha, ",;");
        char *token_desc = strtok(NULL, "\n");

        if (token_id && token_desc) {
            dados[cont].id = atoi(token_id);
            strncpy(dados[cont].descricao, token_desc, sizeof(dados[cont].descricao) - 1);
            dados[cont].descricao[sizeof(dados[cont].descricao) - 1] = '\0';
            cont++;
        }
    }

    fclose(file);
    *tamanho_saida = cont;
    return dados;
}