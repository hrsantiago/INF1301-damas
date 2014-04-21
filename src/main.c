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
    Tabuleiro *tab = TAB_criar();
    TAB_inicializar(tab);
    TAB_imprimir(tab);
    Peca *peca = TAB_obterPeca(tab, 7, 'h');
    if(peca)
        PEC_imprimir(peca);
    else
        printf("Peca nao encontrada.");
    return 0;
}
