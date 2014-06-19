/*
 * Henrique Santiago
 * Marcelo Resende
 * Rafael Haeusler
*/

#include <stdio.h>
#include "jogo.h"

#ifdef _DEBUG
#include "cespdin.h"
#endif

int main()
{
	Jogo *jogo;
#ifdef _DEBUG
    CED_InicializarControlador();
#endif

    jogo = JOG_criar();
    JOG_rodar(jogo);
    JOG_destruir(jogo);

#ifdef _DEBUG
    if(CED_ObterNumeroEspacosAlocados() != 0)
        printf("Ha um vazamento de memoria.\n");
#endif

    return 0;
}
