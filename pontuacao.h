#ifndef _PONTUACAO_t_H
#define _PONTUACAO_t_H

#include "matrix.h"

int verifica_combinacao_linha(MATRIX_t **m, int linha, int col_inicial);

void busca_combinacao_troca(MATRIX_t **m);

void gera_novas_joias(MATRIX_t **m, int linha, int col_inicial, int joias_iguais);

#endif