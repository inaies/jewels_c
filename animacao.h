#ifndef _ANIMACAO_t_H
#define _ANIMACAO_t_H

#include "matrix.h"
#include "pontuacao.h"

int troca_animacao(MATRIX_t **m, MATRIX_t *sel1, MATRIX_t *sel2);

void troca(MATRIX_t **m, MATRIX_t *sel1, MATRIX_t *sel2);

int animacao_combinacao_linha(MATRIX_t **m, MATRIX_t **m_aux, combinacao_t *joia);

int animacao_combinacao_coluna(MATRIX_t **m, MATRIX_t **m_aux, combinacao_t *joia);

void zera_combinacao(combinacao_t *joia);

void troca_combinacao_linha(MATRIX_t **m, MATRIX_t **aux, combinacao_t *joia);

void troca_combinacao_coluna(MATRIX_t **m, MATRIX_t **m_aux, combinacao_t *joia);

void gera_novas_joias(MATRIX_t **m, MATRIX_t **m_aux, combinacao_t *joia);

#endif