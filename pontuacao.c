#include "pontuacao.h"
#include "time.h"
#define tam 10

int calcula_pontuacao(combinacao_t *joia, int nivel)
{
    int pontuacao_comb;
    if(joia->i1_final == joia->i1_inicio)
    {
        pontuacao_comb = ((joia->j1_final - joia->j1_inicio)+1) * nivel;
    }
    if(joia->j1_final == joia->j1_inicio)
    {
        pontuacao_comb = ( (joia->i1_final - joia->i1_inicio)+1) * nivel;
    }
    return pontuacao_comb;
}

int busca_combinacao(MATRIX_t **m, combinacao_t *joia, int segunda_combinacao, MATRIX_t *sel1, MATRIX_t *sel2)
{
    int comeco2;
    if (segunda_combinacao == 0)
        for (int i = 10; i < 20; i++)
        {
            for (int j = 0; j < 10; j++)
            {
                if(busca_combinacao_troca(m, i, j, joia, 0))
                {
                    return 1;
                }
            }
        }
    else
    {
        comeco2 = joia->j2_inicio + 1;
        for (int i = joia->i2_inicio; i < 20; i++)
        {
            for (int j = comeco2; j < 10; j++)
            {
                if (busca_combinacao_troca(m, i, j, joia, 1))
                {
                    return 1;
                }
            }
            comeco2 = 0;
        }
    }
    return 0;
}

int busca_combinacao_troca(MATRIX_t **m, int joia_x, int joia_y, combinacao_t *joia, int segunda_combinacao)
{
    int i1 = joia_x, j1 = joia_y;

    while ((j1 < 9) && (m[joia_x][(j1 + 1)].joias == m[joia_x][joia_y].joias))
        j1++;

    while((i1 < 19)&&(m[(i1 + 1)][joia_y].joias == m[joia_x][joia_y].joias))
        i1++;

    if(((i1 - joia_x) < 2) && ((j1 - joia_y) < 2))
        return 0;

    if(segunda_combinacao == 0)
    {
        if((i1 - joia_x) >= 2)
        {
            joia->i1_inicio = joia_x;
            joia->j1_inicio = joia_y;
            joia->i1_final = i1;
            joia->j1_final = joia_y;
        }

        if((j1 - joia_y) >= 2)
        {
            joia->i1_inicio = joia_x;
            joia->j1_inicio = joia_y;
            joia->i1_final = joia_x;
            joia->j1_final = j1;
        }

        joia->tipo_joia_comb = m[joia_x][joia_y].joias;
        joia->i2_inicio = joia_x;
        joia->j2_inicio = joia->j1_final;
    }
    else
    {
        if(joia->tipo_joia_comb == m[joia_x][joia_y].joias)
            return 0;
        if ((i1 - joia_x) >= 2)
        {
            joia->i2_inicio = joia_x;
            joia->j2_inicio = joia_y;
            joia->i2_final = i1;
            joia->j2_final = joia_y;
        }

        if((j1 - joia_y) >= 2)
        {
            joia->i2_inicio = joia_x;
            joia->j2_inicio = joia_y;
            joia->i2_final = joia_x;
            joia->j2_final = j1;
        }
    }

    return 1;
}


