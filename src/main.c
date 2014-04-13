/*
 * Henrique Santiago
 * Marcelo Resende
 * Rafael Haeusler
*/

#include <stdio.h>
#include "tabuleiro.h"

int main()
{
    Tabuleiro *tab = TAB_criar();
    TAB_inicializar(tab);
    TAB_imprimir(tab);
    printf("Damas\n");
    return 0;
}
