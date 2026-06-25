#ifndef SEQUENCIAL_H
#define SEQUENCIAL_H

#include "estruturas.h"

int busca_sequencial(Registro *array, int tamanho, int id_alvo);
void medir_desempenho_sequencial(Registro *dados, int tamanho);

#endif