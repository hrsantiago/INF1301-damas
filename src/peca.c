/*
 * Henrique Santiago
 * Marcelo Resende
 * Rafael Haeusler
*/

#include <stdlib.h>
#include <stdio.h>
#include "peca.h"

typedef struct _Peca {
    PecaTipo tipo;
    char caracter;
} Peca;

Peca *PEC_criar(PecaTipo tipo, char caracter)
{
    Peca *peca = (Peca*)malloc(sizeof(Peca));
    peca->tipo = tipo;
    peca->caracter = caracter;
    return peca;
}

void PEC_destruir(Peca *peca)
{
    free(peca);
}

void PEC_imprimir(Peca *peca)
{
    if(peca->tipo == PecaNormal)
        printf("%c|", peca->caracter);
    else
        printf("%c|", toupper(peca->caracter));
}

PecaTipo PEC_obterTipo(Peca *peca)
{
    return peca->tipo;
}

void PEC_setarTipo(Peca *peca, PecaTipo tipo)
{
    peca->tipo = tipo;
}

char PEC_obterCaracter(Peca *peca)
{
    return peca->caracter;
}

void PEC_setarCaracter(Peca *peca, char caracter)
{
    peca->caracter = caracter;
}
