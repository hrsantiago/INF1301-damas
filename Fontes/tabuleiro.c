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

void ListaExcluirPeca(void *pDado)
{
    Peca *peca = (Peca*)pDado;
    PEC_destruir(peca);
}

void ListaExcluirLista(void *pDado)
{
    LIS_tppLista lista = (LIS_tppLista)pDado;
    LIS_DestruirLista(lista);
}

Tabuleiro *TAB_criar()
{
    int x, y;
    Tabuleiro *tabuleiro = (Tabuleiro*)malloc(sizeof(Tabuleiro));
    tabuleiro->lista = LIS_CriarLista(ListaExcluirLista);

    for(y = 0; y < TabuleiroAltura; ++y) {
        LIS_tppLista lista = LIS_CriarLista(ListaExcluirPeca);
        LIS_InserirElementoAntes(tabuleiro->lista, lista);
        for(x = 0; x < TabuleiroLargura; ++x)
            LIS_InserirElementoAntes(lista, NULL);
    }

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
    int x, y;
    assert(tabuleiro);

    LIS_IrInicioLista(tabuleiro->lista);
    for(y = 0; y < TabuleiroAltura; ++y) {
        LIS_tppLista lista = (LIS_tppLista)LIS_ObterValor(tabuleiro->lista);
        LIS_IrInicioLista(lista);
        for(x = 0; x < TabuleiroLargura; ++x) {
            Peca *peca = NULL;
            if(y < 2 && (x + y) % 2 == 1)
                peca = PEC_criar(PecaNormal, 'x');
            else if(y > TabuleiroAltura - 3 && (x + y) % 2 == 1)
                peca = PEC_criar(PecaNormal, 'o');

            LIS_SetarValor(lista, peca);
            LIS_AvancarElementoCorrente(lista, 1);
        }
        LIS_AvancarElementoCorrente(tabuleiro->lista, 1);
    }
}

void TAB_imprimir(Tabuleiro *tabuleiro)
{
    int x, y;
    assert(tabuleiro);

    LIS_IrFinalLista(tabuleiro->lista);
    for(y = TabuleiroAltura - 1; y >= 0; --y) {
        LIS_tppLista lista; 
		printf("%d|", y+1);

        lista = (LIS_tppLista)LIS_ObterValor(tabuleiro->lista);
        LIS_IrInicioLista(lista);
        for(x = 0; x < TabuleiroLargura; ++x) {
            Peca *peca = LIS_ObterValor(lista);
            if(peca)
                PEC_imprimir(peca);
            else
                printf(" |");

            LIS_AvancarElementoCorrente(lista, 1);
        }
        printf("\n");
        LIS_AvancarElementoCorrente(tabuleiro->lista, -1);
    }
    printf(" |A|B|C|D|E|F|G|H|\n");
}

Peca *TAB_obterPeca(Tabuleiro *tabuleiro, int linha, char coluna)
{
	LIS_tppLista lista;
    assert(tabuleiro);

    --linha;
    coluna = tolower(coluna) - 'a';

    assert(linha >= 0 && linha <= TabuleiroAltura);
    assert(coluna >= 0 && coluna <= TabuleiroLargura);

    LIS_IrIndice(tabuleiro->lista, linha);
    lista = (LIS_tppLista)LIS_ObterValor(tabuleiro->lista);
    LIS_IrIndice(lista, coluna);
    return LIS_ObterValor(lista);
}
