#include "pontuacao.h"
#include "time.h"
#define tam 10

int busca_combinacao(MATRIX_t **m, combinacao_t *joia)
{
    for (int i = 10; i < 20; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            if(busca_combinacao_troca(m, i, j, joia))
                return 1;
        }
    }
    return 0;
}

int busca_combinacao_troca(MATRIX_t **m, int joia_x, int joia_y, int joia2_x, int joia2_y, combinacao_t *joia)
{
    int i1 = joia_x, j1 = joia_y;
    int i2 = joia2_x, j2 = joia2_y;

    while ((j1 < 9) && (m[joia_x][(j1 + 1)].joias == m[joia_x][joia_y].joias))
        j1++;

    while((i < 19)&&(m[(i + 1)][joia_y].joias == m[joia_x][joia_y].joias))
        i1++;

    while ((j2 < 9) && (m[joia2_x][(j2 + 1)].joias == m[joia2_x][joia2_y].joias))
        j2++;

    while((i2 < 19)&&(m[(i2 + 1)][joia2_y].joias == m[joia2_x][joia2_y].joias))
        i2++;

    if(((i1 - joia_x) < 2) && ((j1 - joia_y) < 2) && ((i2 - joia2_x) < 2) && ((j2 - joia2_y) < 2))
        return 0;

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

    if((i2 - joia2_x) >= 2)
    {
        joia->i2_inicio = joia2_x;
        joia->j2_inicio = joia2_y;
        joia->i2_final = i2;
        joia->j2_final = joia2_y;
    }

    if((j2 - joia2_y) >= 2)
    {
        joia->i2_inicio = joia2_x;
        joia->j2_inicio = joia2_y;
        joia->i2_final = joia2_x;
        joia->j2_final = j2;
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

void gera_novas_joias(MATRIX_t **m, combinacao_t *joia)
{
    //combinacao em linha
    if(joia->i1_inicio == joia->i1_final)
        for(int j = joia->j1_inicio; j < joia->j1_final; j++)
        {
            substitui_acima(m, joia->i1_inicio, j);
        }

    //combinacao em coluna
    if(joia->j1_inicio == joia->j1_final)
    for (int i = joia->i2_inicio; i < joia->i2_final; i++)
    {
            substitui_acima(m, i, joia->j1_inicio);
    }
}


