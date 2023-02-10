#ifndef _MATRIX_t_H
#define _MATRIX_t_H

#include "lib.h"

enum JOIAS
{
    joia_amarela,
    joia_azul,
    joia_verde,
    joia_rosa,
};
typedef enum JOIAS JOIAS_t;

struct MATRIX
{
    int px, py;
    int i, j;
    JOIAS_t joias;
    int sel, clicked;
};
typedef struct MATRIX MATRIX_t;

int testa_linha(MATRIX_t **m, int i, int j);

int testa_coluna(MATRIX_t **m, int i, int j);

MATRIX_t** inicia_matrix(int tam);

void desenha_matrix(MATRIX_t **m);

#endif