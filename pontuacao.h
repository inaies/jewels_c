#ifndef _PONTUACAO_t_H
#define _PONTUACAO_t_H

#include "matrix.h"

struct combinacao
{
    int inicio, final, linha_col, posicao;
};
typedef struct combinacao combinacao_t;

int verifica_combinacao_linha(MATRIX_t **m, int linha, int col_inicial);

combinacao_t busca_combinacao_troca(MATRIX_t **m, int joia_x, int joia_y);

void gera_novas_joias(MATRIX_t **m, int linha, int col_inicial, combinacao_t comb1, combinacao_t comb2);

#endif