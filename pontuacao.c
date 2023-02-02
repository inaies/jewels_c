#include "pontuacao.h"
#include "time.h"
#define tam 10

combinacao_t busca_combinacao_troca(MATRIX_t **m, int joia_x, int joia_y)
{
    combinacao_t comb;
    int i = joia_x, j = joia_y;
    while((m[joia_x][(j-1)].joias == m[joia_x][joia_y].joias)&&(j >= 0))
        j--;

    comb.inicio = j;
    comb.linha_col = 1;
    comb.posicao = joia_x;

    while((m[joia_x][(j+1)].joias == m[joia_x][joia_y].joias)&&(j < 10))
        j++;

    comb.final = j;

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

void gera_novas_joias(MATRIX_t **m, int linha, int col_inicial, combinacao_t comb1, combinacao_t comb2)
{
    printf("inicio: %d - %d \n", comb1.inicio, comb1.final);

        for (int j = comb1.inicio; j <= comb1.final; j++)
        {
            printf("%d \n", j);
            m[comb1.posicao][j].sel = 3;
        }

        for (int j = comb2.inicio; j <= comb2.final; j++)
        {
            printf("%d \n", j);
            m[comb2.posicao][j].sel = 3;
        }
}