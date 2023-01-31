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
    int x, y;
    JOIAS_t joias;
};
typedef struct MATRIX MATRIX_t;

MATRIX_t** inicia_matrix(int tam);

void desenha_matrix(MATRIX_t **m);

#endif