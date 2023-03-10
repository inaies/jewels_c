#include "matrix.h"
#include "lib.h"
#include <stdlib.h>
#include <stdio.h>
#define display_size 700

extern sprites_t sprite;

int testa_linha(MATRIX_t **m, int i, int j)
{
    if(j >= 2)
    {
        if((m[i][j].joias == m[i][j-1].joias)&&(m[i][j].joias == m[i][j-2].joias))
            return 1;
    }
    return 0;
}

int testa_coluna(MATRIX_t **m, int i, int j)
{
    if(i >= 2)
    {
        if((m[i][j].joias == m[i-1][j].joias)&&(m[i][j].joias == m[i-2][j].joias))
            return 1;
    }
    return 0;
}

MATRIX_t** inicia_matrix(int tam)
{
    int dx = 220;

    MATRIX_t **m;

    m = malloc(sizeof(MATRIX_t) * 20);
    if(m == NULL)
    {
        perror("erro ao iniciar matrix");
        exit(1);
    }

    for (int i = 0; i < 20; i++)
    {
        m[i] = malloc(sizeof(MATRIX_t) * tam);
        if(m[i] == NULL)
        {
            perror("erro ao iniciar matrix");
            exit(1);
        }
        for (int j = 0; j < tam; j++)
        {
            if(i>=10)
            {
                m[i][j].px = display_size/2 - dx;
                m[i][j].py = -450 + 50*i;
            }
            else
            {
                m[i][j].px = display_size/2 - dx;
                m[i][j].py = -450 + 50*i;
                m[i][j].sel = 3;
            }
                dx -= 50;

                m[i][j].i = i;
                m[i][j].j = j;
                m[i][j].joias = rand() % 4;

                while ((testa_coluna(m, i, j)) || (testa_linha(m, i, j)))
                m[i][j].joias = rand() % 4;
            
        }
            dx = 220;
    }
    return m;
}

void desenha_matrix(MATRIX_t **m, game_addons_t *addon, int pontuacao)
{
    al_draw_textf(addon->font, al_map_rgb(255, 255, 255), 10, 10, 0, "pontuacao %d ", pontuacao);
    for(int i = 0; i < 20; i++)
    {
        for(int j = 0; j < 10; j++)
        {
            switch(m[i][j].joias)
            {
                case(0):
                    desenha_joia(sprite.amarela, 50, 50, m[i][j].px, m[i][j].py, m[i][j].sel);
                    break;
                case(1):
                    desenha_joia(sprite.azul, 50, 50, m[i][j].px, m[i][j].py, m[i][j].sel);
                    break;
                case(2):
                    desenha_joia(sprite.verde, 50, 50, m[i][j].px, m[i][j].py, m[i][j].sel);
                    break;
                case(3):
                    desenha_joia(sprite.rosa, 50, 50, m[i][j].px, m[i][j].py, m[i][j].sel);
                    break;
            }
        }
    }
}