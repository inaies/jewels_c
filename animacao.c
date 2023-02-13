#include "animacao.h"
#include "matrix.h"

int troca_animacao(MATRIX_t **m, MATRIX_t *sel1, MATRIX_t *sel2)
{
    int joia_aux;
    int j1_x = sel1->i, j1_y = sel1->j, j2_x = sel2->i, j2_y = sel2->j;
    joia_aux = m[j1_x][j1_y].joias;
    // m[j1_x][j1_y].joias = m[j2_x][j2_y].joias;
    // m[j2_x][j2_y].joias = joia_aux;
    m[j1_x][j1_y].sel = 0;
    m[j2_x][j2_y].sel = 0;

    printf(" j1 px %d j2 px %d \n", m[j1_x][j1_y].px, m[j2_x][j2_y].px);
    printf(" j1 py %d j2 py %d \n", m[j1_x][j1_y].py, m[j2_x][j2_y].py);

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

int animacao_combinacao_linha(MATRIX_t **m, MATRIX_t **m_aux, combinacao_t *joia)
{
    int aux = m[joia->i1_inicio][joia->j1_inicio].py;
    m_aux = m;

    for (int j = joia->j1_inicio; j <= joia->j1_final; j++)
    {
        m[joia->i1_inicio][j].sel = 3;
    }

    for (int j = joia->j1_inicio; j <= joia->j1_final; j++)
    {
        for (int i = (joia->i1_inicio - 1); i >= 9; i--)
        {
            if (m[i][joia->j1_final].py >= aux)
                return 1;
            m[i][j].sel = 0;
            m[i][j].py += 5;
        }
    }
    return 0;
}

void gera_novas_joias(MATRIX_t **m, combinacao_t *joia)
{
    int tam_combinacao = joia->i1_final - joia->i1_inicio + 1;
    for (int i = 0; i < tam_combinacao; i++)
    {
        m[i][joia->i1_inicio].px = 130;
        m[i][joia->j1_inicio].py = 50;
        m[i][joia->j1_inicio].sel = 3;

        m[i][joia->j1_inicio].joias = rand() % 4;

        while ((testa_coluna(m, i, joia->j1_inicio)) || (testa_linha(m, i, joia->j1_inicio)))
            m[i][joia->j1_inicio].joias = rand() % 4;
    }

}

int animacao_combinacao_coluna(MATRIX_t **m, MATRIX_t **m_aux, combinacao_t *joia)
{
    int aux = m[joia->i1_final][joia->j1_inicio].py;
    m_aux = m;

    for (int i = joia->i1_inicio; i <= joia->i1_final; i++)
        m[i][joia->j1_inicio].sel = 3;

    for (int i = (joia->i1_inicio-1); i >= 0; i--)
    {
        if(m[i][joia->j1_inicio].py >= aux)
            return 1;
        m[i][joia->j1_inicio].sel = 0;
        m[i][joia->j1_inicio].py += 5;
    }

    return 0;
}

void troca_combinacao_coluna(MATRIX_t **m, MATRIX_t **m_aux, combinacao_t *joia)
{
    int tam_combinacao = joia->i1_final - joia->i1_inicio + 1;
    printf("%d \n", tam_combinacao);

    for (int i = joia->i1_final; i >= 0; i--)
    {
        if(i >= 10)
        {
            m[i][joia->j1_inicio].joias = m[(i - tam_combinacao)][joia->j1_inicio].joias;
            m[i][joia->j1_inicio].px = m_aux[i][joia->j1_inicio].px;
            m[i][joia->j1_inicio].py = m_aux[i][joia->j1_inicio].py;
            m[i][joia->j1_inicio].sel = 0;
        }
        else
            m[i][joia->j1_inicio].sel = 3;
    }
}

void zera_combinacao(combinacao_t *joia)
{
    joia->i1_inicio = 0;
    joia->i1_final = 0;
    joia->j1_inicio = 0;
    joia->j1_final = 0;
    joia->i2_inicio = 0;
    joia->i2_final = 0;
    joia->j2_inicio = 0;
    joia->j2_final = 0;
}

void troca_combinacao_linha(MATRIX_t **m, MATRIX_t **m_aux, combinacao_t *joia)
{

    for (int j = joia->j1_inicio; j <= joia->j1_final; j++)
    {
        for (int i = joia->i1_inicio; i >= 0; i--)
        {
            if(i > 0)
            {
                m[i][j].joias = m[(i - 1)][j].joias;
                m[i][j].px = m_aux[i][j].px;
                m[i][j].py = m_aux[i][j].py;
                if(i>=10)
                    m[i][j].sel = 0;
                else
                    m[i][j].sel = 3;
            }
            if(i == 0)
            {
                m[i][j].px = 130;
                m[i][j].py = 50;
                m[i][j].sel = 3;

                m[i][j].joias = rand() % 4;

                while ((testa_coluna(m, i, j)) || (testa_linha(m, i, j)))
                m[i][j].joias = rand() % 4;
            }
        }
        m[joia->i1_inicio][j].sel = 0;
    }

}