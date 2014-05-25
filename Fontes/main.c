/*
 * Henrique Santiago
 * Marcelo Resende
 * Rafael Haeusler
*/

#include <stdio.h>
#include "jogo.h"

int main()
{
    Jogo *jogo = JOG_criar();
    JOG_rodar(jogo);
    JOG_destruir(jogo);
    return 0;
}
