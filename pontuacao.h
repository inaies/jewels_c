#ifndef _PONTUACAO_t_H
#define _PONTUACAO_t_H

#include "matrix.h"

struct combinacao
{
    int i1_inicio, j1_inicio, i1_final, j1_final;
    int i2_inicio, j2_inicio, i2_final, j2_final;
    JOIAS_t tipo_joia_comb;
};
typedef struct combinacao combinacao_t;

int verifica_combinacao_linha(MATRIX_t **m, int linha, int col_inicial);

int busca_combinacao_troca(MATRIX_t **m, int joia_x, int joia_y, combinacao_t *joia, int segunda_combinacao);

// void gera_novas_joias(MATRIX_t **m, combinacao_t *joia);

void gera_nova_linha(MATRIX_t **m);

int busca_combinacao(MATRIX_t **m, combinacao_t *joia, int segunda_combinacao); 

void substitui_acima(MATRIX_t **m, int i, int j);

#endif