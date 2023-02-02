#ifndef _MOUSE_t_H
#define _MOUSE_t_H

#include "matrix.h"
#include "pontuacao.h"

void troca(MATRIX_t **m, int j1_x, int j1_y, int j2_x, int j2_y);

int verifica_joia_selecionada(MATRIX_t **m, int joia_x, int joia_y);

int eh_joia_vizinha(int joia_x, int joia_y, int i, int j);

int mouse_joia(MATRIX_t **m, int mouse_x, int mouse_y, int click);

#endif