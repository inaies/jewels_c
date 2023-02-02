#include "pontuacao.h"
#include "time.h"
#define tam 10

void busca_combinacao_troca(MATRIX_t **m)
{
    int joias_iguais;
    for (int i = 0; i < tam; i++)
    {
        for (int j = 0; j < tam; j++)
        {
            joias_iguais = verifica_combinacao_linha(m, i, j);
            if (joias_iguais >= 3)
                gera_novas_joias(m, i, j, joias_iguais);
        }
    }
}

int verifica_combinacao_linha(MATRIX_t **m, int linha, int col_inicial)
{
    int qntd_joias = 0;
    int j = col_inicial;
    while (m[linha][j].joias == m[linha][j + 1].joias)
    {
        printf("joia igual encontrada \n");
        j += 1;
        qntd_joias += 1;
    }
    return qntd_joias;
}

void gera_novas_joias(MATRIX_t **m, int linha, int col_inicial, int joias_iguais)
{
    for (int j = col_inicial; j < joias_iguais; j++)
    {
        m[linha][j].joias = rand() % 4;
        // while((testa_coluna(m, linha, j))||(testa_linha(m, linha, j)))
        //     m[linha][j].joias = rand() % 4;
    }
}