#include "mouse.h"
#define tam 10

int verifica_joia_selecionada(MATRIX_t **m, int x_joia, int y_joia)
{
    for (int i = 0; i < tam; i++)
    {
        for (int j = 0; j < tam; j++)
        {
            if(m[i][j].sel == 2)
                return 1;
        }
    }
    return 0;
}

int mouse_joia(MATRIX_t **m, int mouse_x, int mouse_y, int click)
{
    for (int i = 0; i < tam; i++)
    {
        for (int j = 0; j < tam; j++)
        {
            if(((mouse_x >= m[i][j].x)&&(mouse_x <= (m[i][j].x+40)))&&(mouse_y >= m[i][j].y)&&(mouse_y <= m[i][j].y+40))
            {
                if(click == 1)
                {
                    if(m[i][j].sel == 2)
                        m[i][j].sel = 0;
                    else if(!(verifica_joia_selecionada(m, i, j)))
                        m[i][j].sel = 2;
                }
                else if(m[i][j].sel != 2)
                    m[i][j].sel = 1;
                return 1;
            }
            else if((m[i][j].sel != 2))
                m[i][j].sel = 0;
        }
    }
    return 0;
}