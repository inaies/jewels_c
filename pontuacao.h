#ifndef _PONTUACAO_t_H
#define _PONTUACAO_t_H

#include "matrix.h"

struct combinacao
{
    int i1_inicio, j1_inicio, i1_final, j1_final;
    int i2_inicio, j2_inicio, i2_final, j2_final;
    JOIAS_t tipo_joia_comb;
    int selected_X, selectedY;
};
typedef struct combinacao combinacao_t;

int calcula_pontuacao(combinacao_t *joia, int nivel);

int busca_combinacao_troca(MATRIX_t **m, int joia_x, int joia_y, combinacao_t *joia, int segunda_combinacao);

int busca_combinacao(MATRIX_t **m, combinacao_t *joia, int segunda_combinacao,  MATRIX_t *sel1, MATRIX_t *sel2); 


#endif