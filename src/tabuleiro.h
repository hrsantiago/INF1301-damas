/*
 * Henrique Santiago
 * Marcelo Resender
 * Rafael Haeusler
*/

#ifndef TABULEIRO_H
#define TABULEIRO_H

typedef struct _Tabuleiro Tabuleiro;

Tabuleiro *TAB_criar();
void TAB_destruir(Tabuleiro *tabuleiro);
// void TAB_moverPeca();
void TAB_imprimir(Tabuleiro *tabuleiro);
// void TAB_movimentosPossiveis();

#endif
