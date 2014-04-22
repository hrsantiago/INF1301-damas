/*
 * Henrique Santiago
 * Marcelo Resende
 * Rafael Haeusler
*/

#include <assert.h>
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
    PEC_setarTipo(peca, tipo);
    PEC_setarCaracter(peca, caracter);
    return peca;
}

void PEC_destruir(Peca *peca)
{
    assert(peca);
    free(peca);
}

void PEC_imprimir(Peca *peca)
{
    assert(peca);
    if(peca->tipo == PecaNormal)
        printf("%c|", peca->caracter);
    else
        printf("%c|", toupper(peca->caracter));
}

PecaTipo PEC_obterTipo(Peca *peca)
{
    assert(peca);
    return peca->tipo;
}

void PEC_setarTipo(Peca *peca, PecaTipo tipo)
{
    assert(peca);
    assert(tipo == PecaNormal || tipo == PecaDama);
    peca->tipo = tipo;
}

char PEC_obterCaracter(Peca *peca)
{
    assert(peca);
    return peca->caracter;
}

void PEC_setarCaracter(Peca *peca, char caracter)
{
    assert(peca);
    assert(islower(caracter));
    peca->caracter = caracter;
}
