#include "matrix.h"
#include "lib.h"
#include <stdlib.h>
#include <stdio.h>

MATRIX_t** inicia_matrix(int tam)
{
    int dx = 30, dy = 0;

    MATRIX_t **m;

    m = malloc(sizeof(MATRIX_t) * tam);
    // if(m == NULL)
    // {
    //     perror("erro ao iniciar matrix");
    //     exit(1);
    // }

    for (int i = 0; i < tam; i++)
    {
        m[i] = malloc(sizeof(MATRIX_t) * tam);
        // if(m[i] == NULL)
        // {
        //     perror("erro ao iniciar matrix");
        //     exit(1);
        // }
        for (int j = 0; j < tam; j++)
        {
            m[i][j].x = 700/2 - dx;
            m[i][j].y = dy;
            m[i][j].joias = rand() % 5;
            dx -= 30;
        }
        dx = 25;
        dy += 30;
    }
    return m;
}

void desenha_matrix(MATRIX_t **m)
{
    for(int i = 0; i < 8; i++)
    {
        for(int j = 0; j < 8; j++)
        {
            switch(m[i][j].joias)
            {
                case(0):
                    desenha_joia(sprite->amarela, 50, 50, m[i][j].x, m[i][j].y);
                    break;
                case(1):
                    desenha_joia(sprite->azul, 50, 50, m[i][j].x, m[i][j].y);
                    break;
                case(2):
                    desenha_joia(sprite->verde, 50, 50, m[i][j].x, m[i][j].y);
                    break;
                case(3):
                    desenha_joia(sprite->rosa, 50, 50, m[i][j].x, m[i][j].y);
                    break;
            }
        }
    }

}