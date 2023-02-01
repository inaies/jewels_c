#ifndef _MOUSE_t_H
#define _MOUSE_t_H

#include "matrix.h"

int verifica_joia_selecionada(MATRIX_t **m, int x_joia, int y_joia);

int mouse_joia(MATRIX_t **m, int mouse_x, int mouse_y, int click);

#endif