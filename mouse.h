#ifndef _MOUSE_t_H
#define _MOUSE_t_H

#include "matrix.h"
#include "pontuacao.h"

void troca(MATRIX_t **m, MATRIX_t *sel1, MATRIX_t *sel2);

int verifica_joia_selecionada(MATRIX_t **m, int joia_x, int joia_y, MATRIX_t *sel2);

int eh_joia_vizinha(int joia_x, int joia_y, int i, int j);

int mouse_joia(MATRIX_t **m, int mouse_x, int mouse_y, int click, MATRIX_t *sel1, MATRIX_t *sel2);


#endif