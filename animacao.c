#include "animacao.h"
#include "matrix.h"
#define display_size 700

int troca_animacao(MATRIX_t **m, MATRIX_t *sel1, MATRIX_t *sel2)
{
    int joia_aux;
    int j1_x = sel1->i, j1_y = sel1->j, j2_x = sel2->i, j2_y = sel2->j;
    joia_aux = m[j1_x][j1_y].joias;
    // m[j1_x][j1_y].joias = m[j2_x][j2_y].joias;
    // m[j2_x][j2_y].joias = joia_aux;
    m[j1_x][j1_y].sel = 0;
    m[j2_x][j2_y].sel = 0;

    //printf(" j1 px %d j2 px %d \n", m[j1_x][j1_y].px, m[j2_x][j2_y].px);
    //printf(" j1 py %d j2 py %d \n", m[j1_x][j1_y].py, m[j2_x][j2_y].py);

    if(sel1->i == sel2->i)
    {
        if(sel1->j < sel2->j)
        {
            if(m[j1_x][j1_y].px < sel2->px)
            {
                m[j1_x][j1_y].px += 5;
                m[j2_x][j2_y].px -= 5;
            }
            else
                return 1;
        }
        else
        {
            if(m[j1_x][j1_y].px > sel2->px)
            {
                m[j1_x][j1_y].px -= 5;
                m[j2_x][j2_y].px += 5;
            }
            else
                return 1;
        }
    }   
    if(sel1->j == sel2->j)
    {
        if(sel1->i < sel2->i)
        {
            if(m[j1_x][j1_y].py < sel2->py)
            {
                m[j1_x][j1_y].py += 5;
                m[j2_x][j2_y].py -= 5;
            }
            else
                return 1;
        }
        else
        {
            if(m[sel1->i][sel1->j].py > sel2->py)
            {
                m[j1_x][j1_y].py -= 5;
                m[j2_x][j2_y].py += 5;
            }
            else
                return 1;
        }
    }

    return 0;
}

void troca(MATRIX_t **m, MATRIX_t *sel1, MATRIX_t *sel2)
{
    MATRIX_t aux = m[sel2->i][sel2->j];
    m[sel2->i][sel2->j] = m[sel1->i][sel1->j];
    m[sel1->i][sel1->j] = aux;

    m[sel1->i][sel1->j].i = sel1->i;
    m[sel1->i][sel1->j].j = sel1->j;
    m[sel1->i][sel1->j].px = sel1->px;
    m[sel1->i][sel1->j].py = sel1->py;
    m[sel2->i][sel2->j].i = sel2->i;
    m[sel2->i][sel2->j].j = sel2->j;
    m[sel2->i][sel2->j].px = sel2->px;
    m[sel2->i][sel2->j].py = sel2->py;
    
}

int animacao_combinacao_linha(MATRIX_t **m, combinacao_t *joia)
{
    int aux = m[joia->i1_inicio][joia->j1_inicio].py;

    for (int j = joia->j1_inicio; j <= joia->j1_final; j++)
        m[joia->i1_inicio][j].sel = 3;

    // if((joia->i2_inicio == joia->i2_final)&&(joia->i2_inicio != -1))
    // {
    //     for(int j = joia->j2_inicio; j <= joia->j2_final; j++)
    //         m[joia->i2_inicio][j].sel = 3;

    //     if((joia->j1_inicio == joia->j2_inicio)&&(joia->j1_final == joia->j2_final))
    //     {
    //         for (int j = joia->j2_inicio; j <= joia->j2_final; j++)
    //         {
    //             for (int i = (joia->i1_inicio - 2); i > 0; i--)
    //             {
    //                 if (m[i][joia->j1_final].py >= aux)
    //                     return 1;
    //                 m[i][j].sel = 0;
    //                 m[i][j].py += 5;
    //             }
    //         }
    //     }
    // }
    // else
    // {
        for (int j = joia->j1_inicio; j <= joia->j1_final; j++)
        {
            for (int i = (joia->i1_inicio - 1); i > 0; i--)
            {
                if (m[i][joia->j1_final].py >= aux)
                    return 1;
                if (i == 9)
                    m[i][j].sel = 0;
                m[i][j].py += 2;
            }
        }
    // }
    return 0;
}

void gera_novas_joias(MATRIX_t **m, combinacao_t *joia)
{
    int j = joia->j1_inicio;
    int tam_combinacao = joia->i1_final - joia->i1_inicio + 1;
    for (int i = 0; i < tam_combinacao; i++)
    {
        m[i][j].sel = 3;
        m[i][j].joias = rand() % 4;

        while ((testa_coluna(m, i, j)) || (testa_linha(m, i, j)))
            m[i][j].joias = rand() % 4;
    }
}

int animacao_combinacao_coluna(MATRIX_t **m, combinacao_t *joia)
{
    int j = joia->j1_inicio;

    int aux = m[joia->i1_final][j].py;

    for (int i = joia->i1_inicio; i <= joia->i1_final; i++)
        m[i][j].sel = 3;

    int tam_combinacao = joia->i1_final - joia->i1_inicio + 1;
    for (int i = (joia->i1_inicio-1); i >= 10 - tam_combinacao; i--)
    {
        if(m[i][j].py > aux)
            return 1;
        m[i][j].sel = 0;
        m[i][j].py += 2;
    }

    return 0;
}

void arruma_px_py_matriz(MATRIX_t **m) {
    for (int i = 0; i < 20; i++) {
        for (int j = 0; j < 10; j++) {
            m[i][j].px = 130 + j*50;
            m[i][j].py = -450 + i*50;
            m[i][j].sel = i >= 10 ? 0 : 3;
        }
    }
}

void troca_combinacao_coluna(MATRIX_t **m, combinacao_t *joia)
{
    int tam_combinacao = joia->i1_final - joia->i1_inicio + 1;
    int j = joia->j1_inicio;
    for (int i = joia->i1_final; i >= 0; i--)
    {
        if(i > tam_combinacao)
        {
            m[i][j].joias = m[(i - tam_combinacao)][j].joias;
        }
    }
    arruma_px_py_matriz(m);
}

void zera_combinacao(combinacao_t *joia)
{
    joia->i1_inicio = -1;
    joia->i1_final = -1;
    joia->j1_inicio = -1;
    joia->j1_final = -1;
    joia->i2_inicio = -1;
    joia->i2_final = -1;
    joia->j2_inicio = -1;
    joia->j2_final = -1;
}

void troca_combinacao_linha(MATRIX_t **m, combinacao_t *joia, int qntd_comb)
{
    // m = m_aux;

    for (int j = joia->j1_inicio; j <= joia->j1_final; j++)
    {
        for (int i = joia->i1_inicio; i >= 1; i--)
        {
            m[i][j].joias = m[(i - 1)][j].joias;
        }
    }

    arruma_px_py_matriz(m);
}