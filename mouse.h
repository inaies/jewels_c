#ifndef _MOUSE_t_H
#define _MOUSE_t_H

#include "matrix.h"

void verifica_joia_selecionada(MATRIX_t **m, int joia_x, int joia_y);

int eh_joia_vizinha(int x_joia, int y_joia, int i, int j);

int mouse_joia(MATRIX_t **m, int mouse_x, int mouse_y, int click);

#endif