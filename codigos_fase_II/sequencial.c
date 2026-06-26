#include <stdlib.h>
#include "sequencial.h"

Registro* busca_sequencial(Registro *dados, int tamanho, int id) {
    for (int i = 0; i < tamanho; i++) {
        if (dados[i].id == id) {
            return &dados[i];
        }
    }
    return NULL;
}