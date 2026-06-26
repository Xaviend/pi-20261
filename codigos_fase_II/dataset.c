#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dataset.h"

int carregar_dataset(const char *caminho, Registro **dados) {
    FILE *f = fopen(caminho, "r");
    if (!f) return 0;

    int capacidade = 1000;
    int tamanho = 0;
    *dados = malloc(capacidade * sizeof(Registro));
    char linha[256];

    fgets(linha, sizeof(linha), f);

    while (fgets(linha, sizeof(linha), f)) {
        if (tamanho >= capacidade) {
            capacidade *= 2;
            *dados = realloc(*dados, capacidade * sizeof(Registro));
        }

        char *token = strtok(linha, ",");
        if(token) (*dados)[tamanho].id = atoi(token);

        token = strtok(NULL, ",");
        if(token) strcpy((*dados)[tamanho].nome, token);

        token = strtok(NULL, ",");
        if(token) strcpy((*dados)[tamanho].categoria, token);

        token = strtok(NULL, "\n");
        if(token) (*dados)[tamanho].valor = atof(token);

        tamanho++;
    }

    fclose(f);
    return tamanho;
}