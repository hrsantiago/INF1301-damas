/*
 * Henrique Santiago
 * Marcelo Resende
 * Rafael Haeusler
*/

#ifndef PECA_H
#define PECA_H

typedef enum _PecaTipo {
    PecaNormal,
    PecaDama
} PecaTipo;

typedef struct _Peca Peca;

Peca *PEC_criar(PecaTipo tipo, char caracter);
void PEC_destruir(Peca *peca);
void PEC_imprimir(Peca *peca);
PecaTipo PEC_obterTipo(Peca *peca);
void PEC_setarTipo(Peca *peca, PecaTipo tipo);
char PEC_obterCaracter(Peca *peca);
void PEC_setarCaracter(Peca *peca, char caracter);

#endif
