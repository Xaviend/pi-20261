#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "produto.h"

// Protótipos externos
extern int lerCSV(const char* nomeArquivo, Produto** vetor);
extern int buscaSequencial(int id, Produto *vetor, int tamanho);
extern void liberarVetor(Produto* vetor);

int main() {
    Produto* vetor = NULL;
    int tamanho = lerCSV("dataset3.csv", &vetor);
    
    if (tamanho <= 0) return 1;
    printf("Dados carregados com sucesso! Total de registros: %d\n", tamanho);
    
    // Preparando o cenário exigido pelo protocolo
    int idInicio = vetor[0].id;
    int idMeio = vetor[tamanho / 2].id;
    int idFim = vetor[tamanho - 1].id;
    int idInexistente = -99999;
    
    double somaTempos = 0.0;
    volatile int dummy = 0; // Impede que o compilador ignore a busca por otimização
    
    printf("\nIniciando bateria de testes...\n");
    for(int rep = 1; rep <= 3; rep++) {
        clock_t inicio = clock();
        
        for (int i = 0; i < 1000; i++) {
            dummy += buscaSequencial(idInicio, vetor, tamanho);
            dummy += buscaSequencial(idMeio, vetor, tamanho);
            dummy += buscaSequencial(idFim, vetor, tamanho);
            dummy += buscaSequencial(idInexistente, vetor, tamanho);
        }
        
        clock_t fim = clock();
        double tempoDecorrido = (double)(fim - inicio) / CLOCKS_PER_SEC;
        somaTempos += tempoDecorrido;
        printf("Rodada %d: Tempo = %.6f segundos\n", rep, tempoDecorrido);
    }
    
    // Cálculos finais
    double tempoMedioTotal = somaTempos / 3.0;
    // 4000 buscas por rodada (1000 inícios + 1000 meios + 1000 fins + 1000 inexistentes)
    double tempoMedioBusca = tempoMedioTotal / 4000.0; 
    
    printf("\n--- Resultados Finais ---\n");
    printf("Tempo total acumulado (3 baterias): %.6f s\n", somaTempos);
    printf("Tempo medio por bateria: %.6f s\n", tempoMedioTotal);
    printf("Tempo medio por busca individual: %.9f s\n", tempoMedioBusca);

    liberarVetor(vetor);
    return 0;
}