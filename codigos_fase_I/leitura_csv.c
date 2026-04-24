#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "produto.h"

extern Produto* criarVetor(int tamanho);

int lerCSV(const char* nomeArquivo, Produto** vetor) {
    FILE* file = fopen(nomeArquivo, "r");
    if (!file) {
        fprintf(stderr, "Erro: Arquivo %s não encontrado.\n", nomeArquivo);
        return -1;
    }

    char linha[256];
    int count = 0;
    
    // Pula o cabeçalho
    fgets(linha, sizeof(linha), file); 
    
    // Conta as linhas reais do dataset
    while (fgets(linha, sizeof(linha), file)) {
        count++;
    }

    // Aloca memória (usa a função do alocacao_dinamica.c)
    *vetor = criarVetor(count);
    
    // Voltar pro começo para popular os dados
    rewind(file);
    fgets(linha, sizeof(linha), file); // pula cabeçalho de novo

    int i = 0;
    while (fgets(linha, sizeof(linha), file) && i < count) {
        char* token = strtok(linha, ",");
        if(token) (*vetor)[i].id = atoi(token);
        
        token = strtok(NULL, ",");
        if(token) { strncpy((*vetor)[i].nome, token, 50); (*vetor)[i].nome[50] = '\0'; }
        
        token = strtok(NULL, ",");
        if(token) { strncpy((*vetor)[i].categoria, token, 30); (*vetor)[i].categoria[30] = '\0'; }
        
        token = strtok(NULL, "\r\n");
        if(token) (*vetor)[i].valor = atof(token);
        i++;
    }
    
    fclose(file);
    return count;
}