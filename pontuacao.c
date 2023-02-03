#include "pontuacao.h"
#include "time.h"
#define tam 10

combinacao_t busca_combinacao_troca(MATRIX_t **m, int joia_x, int joia_y)
{
    combinacao_t comb;

    comb.linha = malloc(sizeof(int) * 10);
    comb.coluna = malloc(sizeof(int) * 10);

    int i = joia_x, j = joia_y;
    while((m[joia_x][(j-1)].joias == m[joia_x][joia_y].joias)&&(j >= 0))
    {
        j--;
        comb.linha[j] = 1;
    }

    comb.inicio = j;
    comb.linha_col = 1;
    comb.posicao = joia_x;

    while((m[joia_x][(j+1)].joias == m[joia_x][joia_y].joias)&&(j < 10))
    {
        j++;
        comb.linha[j] = 1;
    }
    comb.final = j;

    if((comb.final - comb.inicio) < 2)
        zera_vetor(comb.linha);

    while((m[(i-1)][joia_y].joias == m[joia_x][joia_y].joias)&&(i >= 10))
    {
        i--;
        comb.coluna[i] = 1;
    }

    comb.inicio = i;
    
    while((m[(i+1)][joia_y].joias == m[joia_x][joia_y].joias)&&(j < 10))
    {
        i++;
        comb.coluna[i] = 1;
    }

    comb.final = i;
    if((comb.final - comb.inicio) < 2)
        zera_vetor(comb.coluna);


    return (comb);
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
    if(i == 0)
        return;
    m[i][j].joias = m[(i-1)][j].joias;
    substitui_acima(m, (i-1), j);
}

void gera_novas_joias(MATRIX_t **m, int linha1, combinacao_t comb)
{
    for(int i = 10; i < 20; i++)
    {
        if(comb.coluna[i] == 1)
            substitui_acima(m, linha1, i);
    }

    for (int j = 0; j < 10; j++)
    {
        if (comb.linha[j] == 1)
            substitui_acima(m, linha1, j);
    }

}


void zera_vetor(int *vetor)
{
    for (int i = 0; i < 10; i++)
        vetor[i] = 0;
}

