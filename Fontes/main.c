/*
 * Henrique Santiago
 * Marcelo Resende
 * Rafael Haeusler
*/

#include <stdio.h>
#include "peca.h"
#include "tabuleiro.h"

int main()
{
    Peca *peca, *peca2, *peca3;
    Tabuleiro *tab = TAB_criar();
    TAB_inicializar(tab);
    TAB_imprimir(tab);
    peca = TAB_obterPeca(tab, 7, 'h');
    if(peca) {
        PEC_imprimir(peca);
        printf("\n");
    }
    else
        printf("Peca nao encontrada.\n");

    peca2 = PEC_criar(PecaDama, 'r');
    TAB_setarPeca(tab, 1, 'a', peca2);
    TAB_imprimir(tab);

    peca3 = PEC_criar(PecaDama, 'g');
    TAB_setarPeca(tab, 2, 'a', peca3);
    TAB_imprimir(tab);

    TAB_destruir(tab);
    return 0;
}
