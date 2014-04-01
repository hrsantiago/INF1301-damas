/*
 * Henrique Santiago
 * Marcelo Resender
 * Rafael Haeusler
*/

#ifndef PECA_H
#define PECA_H

typedef enum _PecaTipo {
    Peca_Normal,
    Peca_Dama
} PecaTipo;

typedef struct _Peca Peca;

Peca *PEC_criar();
void PEC_destruir(Peca *peca);
//void PEC_remover(Peca *peca);
PecaTipo PEC_pegarTipo(Peca *peca);
void PEC_setarTipo(Peca *peca, PecaTipo tipo);

#endif
