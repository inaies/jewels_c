#include "pontuacao.h"
#include "time.h"
#define tam 10

int busca_combinacao(MATRIX_t **m, combinacao_t *joia, int segunda_combinacao)
{
    int comeco1, comeco2;
    if (segunda_combinacao == 0)
        for (int i = 10; i < 20; i++)
        {
            for (int j = 0; j < 10; j++)
            {
                if(busca_combinacao_troca(m, i, j, joia, 0))
                    return 1;
            }
        }
    else
    {
        comeco2 = joia->j2_inicio + 1;
        printf("comeco da segunda procura: %d %d \n", joia->i2_inicio, joia->j2_inicio);
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

int verifica_combinacao_linha(MATRIX_t **m, int linha, int col_inicial)
{
    int qntd_joias = 0;
    int j = col_inicial;
    while (m[linha][j].joias == m[linha][j + 1].joias)
    {
        // printf("joia igual encontrada \n");
        j += 1;
        qntd_joias += 1;
    }
    return qntd_joias;
}

void substitui_acima(MATRIX_t **m, int i, int j)
{
    if(i < 9)
        return;

    m[i][j].joias = m[(i - 1)][j].joias;
    // gera_nova_linha(m);
    substitui_acima(m, (i - 1), j);
}

void gera_nova_linha(MATRIX_t **m)
{
    int i = 0;
    // for (int i = 10; i < 20; i++)
        for (int j = 0; j < 10; j++)
        {
            m[i][j].joias = rand() % 4;

            while ((testa_coluna(m, i, j)) || (testa_linha(m, i, j)))
                m[i][j].joias = rand() % 4;
        }
}

// void gera_novas_joias(MATRIX_t **m, combinacao_t *joia)
// {
//     //combinacao em linha
//     if(joia->i1_inicio == joia->i1_final)
//         for(int j = joia->j1_inicio; j < joia->j1_final; j++)
//         {
//             substitui_acima(m, joia->i1_inicio, j);
//         }

//     //combinacao em coluna
//     if(joia->j1_inicio == joia->j1_final)
//     for (int i = joia->i2_inicio; i < joia->i2_final; i++)
//     {
//             substitui_acima(m, i, joia->j1_inicio);
//     }
// }


