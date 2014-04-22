/*
 * Henrique Santiago
 * Marcelo Resende
 * Rafael Haeusler
*/

#ifndef TABULEIRO_H
#define TABULEIRO_H

typedef struct _Tabuleiro Tabuleiro;
typedef struct _Peca Peca;

Tabuleiro *TAB_criar();
void TAB_destruir(Tabuleiro *tabuleiro);
void TAB_inicializar(Tabuleiro *tabuleiro);
void TAB_imprimir(Tabuleiro *tabuleiro);

// linha 1-8, coluna a-h
Peca *TAB_obterPeca(Tabuleiro *tabuleiro, int linha, char coluna);

#endif
