#include "mouse.h"
#define tam 10

void verifica_joia_selecionada(MATRIX_t **m, int joia_x, int joia_y)
{
    for (int i = 0; i < tam; i++)
    {
        for (int j = 0; j < tam; j++)
        {
            if((m[i][j].sel == 2)&&((i == (joia_x-1))&& (j == joia_y)))
            {   
                if(eh_joia_vizinha(joia_x, joia_y, i, j))
                    m[i][j].sel = 3;
                else 
                    m[i][j].sel = 0;
                // return 1;
            }
        }
    }
    // return 0;
}

int eh_joia_vizinha(int x_joia, int y_joia, int i, int j)
{
    if((j < 10)&&(i < 10))
    {
        if((j == y_joia) && ((i == (x_joia - 1))||(i == (x_joia + 1))))
            return 1;
        if((i == x_joia) && ((j == (y_joia - 1))||(j == (y_joia + 1))))
            return 1;
    }
    // else if(j == 10)
    // {
    //     if((j == y_joia)&&((i == (x_joia - 1))||(i == (x_joia + 1))))
    //         return 1;
    // }
    // else if(i == 10)
    // {
    //     if()
    // }
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
                    else
                    {
                        verifica_joia_selecionada(m, i, j);
                        m[i][j].sel = 2;
                    }
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
