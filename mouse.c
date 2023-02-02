#include "mouse.h"
#define tam 10

void troca(MATRIX_t **m, int j1_x, int j1_y, int j2_x, int j2_y)
{
    int joia_aux;
    joia_aux = m[j1_x][j1_y].joias;
    m[j1_x][j1_y].joias = m[j2_x][j2_y].joias;
    m[j2_x][j2_y].joias = joia_aux;
    m[j1_x][j1_y].sel = 0;
    m[j2_x][j2_y].sel = 0;
}

int verifica_joia_selecionada(MATRIX_t **m, int joia_x, int joia_y)
{
    for (int i = 0; i < tam; i++)
    {
        for (int j = 0; j < tam; j++)
        {
            if(m[i][j].sel == 2)
            {   
                if(eh_joia_vizinha(joia_x, joia_y, i, j))
                {
                    m[joia_x][joia_y].sel = 3;
                    troca(m, joia_x, joia_y, i, j);
                    // busca_combinacao_troca(m);
                    return 0;
                }
                else 
                    m[i][j].sel = 0;
            }
        }
    }
    return 1;
}

int eh_joia_vizinha(int joia_x, int joia_y, int i, int j)
{
    if((j < 10)&&(i < 10))
    {
        if((i == joia_x) && ((j == (joia_y - 1))||(j == (joia_y + 1))))
            return 1;
        if((j == joia_y) && ((i == (joia_x - 1))||(i == (joia_x + 1))))
            return 1;
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
                    else
                    {
                        if(verifica_joia_selecionada(m, i, j))
                            m[i][j].sel = 2;
                    }
                }
                else if(m[i][j].sel != 2)
                    m[i][j].sel = 1;
                return 1;
            }
            else if(m[i][j].sel != 2)
                m[i][j].sel = 0;
        }
    }
    return 0;
}
