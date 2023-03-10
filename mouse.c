#include "mouse.h"
#define tam 10


int verifica_joia_selecionada(MATRIX_t **m, int joia_x, int joia_y, MATRIX_t *sel1)
{

    for (int i = 10; i < 20; i++)
    {
        for (int j = 0; j < tam; j++)
        {
            if(m[i][j].sel == 2)
            {   
                if(eh_joia_vizinha(joia_x, joia_y, i, j))
                { 
                    m[joia_x][joia_y].sel = 3;
                    sel1->i = i;
                    sel1->j = j;
                    sel1->px = m[i][j].px;
                    sel1->py = m[i][j].py;
                    return 1;
                }
                else
                    m[i][j].sel = 0;
            }
        }
    }

    return 0;
}

int eh_joia_vizinha(int joia_x, int joia_y, int i, int j)
{
    if((j < 10)&&(i < 20))
    {
        if((i == joia_x) && ((j == (joia_y - 1))||(j == (joia_y + 1))))
            return 1;
        if((j == joia_y) && ((i == (joia_x - 1))||(i == (joia_x + 1))))
            return 1;
    }
    return 0;
}

int mouse_joia(MATRIX_t **m, int mouse_x, int mouse_y, int click, MATRIX_t *sel1, MATRIX_t *sel2)
{
    for (int i = 10; i < 20; i++)
    {
        for (int j = 0; j < tam; j++)
        {
            if(((mouse_x >= m[i][j].px)&&(mouse_x <= (m[i][j].px+40)))&&(mouse_y >= m[i][j].py)&&(mouse_y <= m[i][j].py+40))
            {
                if(click == 1)
                {
                    if(m[i][j].sel == 2)
                        m[i][j].sel = 0;
                    else
                    {
                        if(!(verifica_joia_selecionada(m, i, j, sel1)))
                            m[i][j].sel = 2;
                        else
                        {
                            sel2->i = i;
                            sel2->j = j;
                            sel2->px = m[i][j].px;
                            sel2->py = m[i][j].py;
                            return 1;
                        }
                    }
                }
                else if((m[i][j].sel != 2)&&(m[i][j].sel != 3))
                    m[i][j].sel = 1;
                return 0;
            }
            else if((m[i][j].sel != 2)&&(m[i][j].sel != 3))
                m[i][j].sel = 0;
        }
    }
    return 0;
}

