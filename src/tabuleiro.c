/*
 * Henrique Santiago
 * Marcelo Resende
 * Rafael Haeusler
*/

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "peca.h"
#include "tabuleiro.h"
#include "lista.h"

enum {
    TabuleiroAltura = 8,
    TabuleiroLargura = 8,
};

typedef struct _Tabuleiro {
    LIS_tppLista lista;
} Tabuleiro;

void ListaExcluirValor(void *pDado)
{
    Peca *peca = (Peca*)pDado;
    PEC_destruir(peca);
}

Tabuleiro *TAB_criar()
{
    Tabuleiro *tabuleiro = (Tabuleiro*)malloc(sizeof(Tabuleiro));
    tabuleiro->lista = LIS_CriarLista(ListaExcluirValor);

    int i;
    for(i = 0; i < TabuleiroAltura * TabuleiroLargura; ++i) // poderia ser /2 ja que as casas brancas/pretas nao sao usadas.
        LIS_InserirElementoAntes(tabuleiro->lista, NULL);

    return tabuleiro;
}

void TAB_destruir(Tabuleiro *tabuleiro)
{
    assert(tabuleiro);
    LIS_DestruirLista(tabuleiro->lista);
    free(tabuleiro);
}

void TAB_inicializar(Tabuleiro *tabuleiro)
{
    assert(tabuleiro);
    int x, y;

    LIS_IrInicioLista(tabuleiro->lista);
    for(y = 0; y < TabuleiroAltura; ++y) {
        for(x = 0; x < TabuleiroLargura; ++x) {
            if(y < 2 && (x + y) % 2 == 1) {
                Peca *peca = PEC_criar(PecaNormal, 'x');
                LIS_SetarValor(tabuleiro->lista, peca);
            }
            else if(y > TabuleiroAltura - 3 && (x + y) % 2 == 1) {
                Peca *peca = PEC_criar(PecaNormal, 'o');
                LIS_SetarValor(tabuleiro->lista, peca);
            }
            else
                LIS_SetarValor(tabuleiro->lista, NULL);

            LIS_AvancarElementoCorrente(tabuleiro->lista, 1);
        }
    }

}

void TAB_imprimir(Tabuleiro *tabuleiro)
{
    assert(tabuleiro);
    int x, y;

    for(y = TabuleiroAltura - 1; y >= 0; --y) {
        printf("%d|", y+1);
        for(x = 0; x < TabuleiroLargura; ++x) {
            LIS_IrIndice(tabuleiro->lista, x, y, TabuleiroLargura);
            Peca *peca = LIS_ObterValor(tabuleiro->lista);
            if(peca)
                PEC_imprimir(peca);
            else
                printf(" |");
        }
        printf("\n");
    }
    printf(" |A|B|C|D|E|F|G|H|\n");
}
