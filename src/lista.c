/*
 * Henrique Santiago
 * Marcelo Resende
 * Rafael Haeusler
*/

/***************************************************************************
*  $MCI Módulo de implementação: LIS  Lista duplamente encadeada
*
*  Arquivo gerado:              LISTA.c
*  Letras identificadoras:      LIS
*
*  Nome da base de software:    Arcabouço para a automação de testes de programas redigidos em C
*  Arquivo da base de software: D:\AUTOTEST\PROJETOS\LISTA.BSW
*
*  Projeto: INF 1301 / 1628 Automatização dos testes de módulos C
*  Gestor:  LES/DI/PUC-Rio
*  Autores: avs
*
*  $HA Histórico de evolução:
*     Versão  Autor    Data     Observações
*     4       avs   01/fev/2006 criar linguagem script simbólica
*     3       avs   08/dez/2004 uniformização dos exemplos
*     2       avs   07/jul/2003 unificação de todos os módulos em um só projeto
*     1       avs   16/abr/2003 início desenvolvimento
*
***************************************************************************/

#include <stdio.h>
#include <string.h>
#include <memory.h>
#include <malloc.h>
#include <assert.h>

#define LISTA_OWN
#include "lista.h"
#undef LISTA_OWN

typedef struct tagElemLista {
    void *pValor;
    struct tagElemLista *pAnt;
    struct tagElemLista *pProx;
} tpElemLista;

typedef struct LIS_tagLista {
    tpElemLista *pOrigemLista;
    tpElemLista *pFimLista;
    tpElemLista *pElemCorr;
    int numElem;
    void (*ExcluirValor)(void *pValor);
} LIS_tpLista;

static void LiberarElemento(LIS_tppLista pLista, tpElemLista *pElem);
static tpElemLista * CriarElemento(LIS_tppLista pLista, void *pValor);
static void LimparCabeca(LIS_tppLista pLista);

LIS_tppLista LIS_CriarLista(void (*ExcluirValor)(void *pDado))
{
    LIS_tpLista *pLista = NULL;
    pLista = (LIS_tpLista*)malloc(sizeof(LIS_tpLista));
    if(pLista == NULL)
        return NULL;

    LimparCabeca(pLista);
    pLista->ExcluirValor = ExcluirValor;
    return pLista;
}

void LIS_DestruirLista(LIS_tppLista pLista)
{
#ifdef _DEBUG
    assert(pLista != NULL);
#endif

    LIS_EsvaziarLista(pLista);
    free(pLista);
}

void LIS_EsvaziarLista(LIS_tppLista pLista)
{
    tpElemLista *pElem;
    tpElemLista *pProx;

#ifdef _DEBUG
    assert(pLista != NULL);
#endif

    pElem = pLista->pOrigemLista;
    while(pElem != NULL) {
        pProx = pElem->pProx;
        LiberarElemento(pLista , pElem);
        pElem = pProx;
    }

    LimparCabeca(pLista);
}

LIS_tpCondRet LIS_InserirElementoAntes(LIS_tppLista pLista, void *pValor)
{
    tpElemLista *pElem;

#ifdef _DEBUG
    assert(pLista != NULL);
#endif

    pElem = CriarElemento(pLista , pValor);
    if(pElem == NULL)
        return LIS_CondRetFaltouMemoria;

    if(pLista->pElemCorr == NULL) {
        pLista->pOrigemLista = pElem;
        pLista->pFimLista = pElem;
    }
    else {
        if(pLista->pElemCorr->pAnt != NULL) {
            pElem->pAnt = pLista->pElemCorr->pAnt;
            pLista->pElemCorr->pAnt->pProx = pElem;
        }
        else
            pLista->pOrigemLista = pElem;

        pElem->pProx = pLista->pElemCorr;
        pLista->pElemCorr->pAnt = pElem;
    }

    pLista->pElemCorr = pElem;
    return LIS_CondRetOK;
}

LIS_tpCondRet LIS_InserirElementoApos(LIS_tppLista pLista , void *pValor)
{
    tpElemLista * pElem;

#ifdef _DEBUG
    assert(pLista != NULL);
#endif

    pElem = CriarElemento(pLista , pValor);
    if(pElem == NULL)
        return LIS_CondRetFaltouMemoria;
    if(pLista->pElemCorr == NULL) {
        pLista->pOrigemLista = pElem;
        pLista->pFimLista = pElem;
    }
    else {
        if(pLista->pElemCorr->pProx != NULL) {
            pElem->pProx = pLista->pElemCorr->pProx;
            pLista->pElemCorr->pProx->pAnt = pElem;
        } else
            pLista->pFimLista = pElem;

        pElem->pAnt = pLista->pElemCorr;
        pLista->pElemCorr->pProx = pElem;
    }

    pLista->pElemCorr = pElem;
    return LIS_CondRetOK;
}

LIS_tpCondRet LIS_ExcluirElemento(LIS_tppLista pLista)
{
    tpElemLista * pElem;

#ifdef _DEBUG
    assert(pLista != NULL);
#endif

    if(pLista->pElemCorr == NULL)
        return LIS_CondRetListaVazia;

    pElem = pLista->pElemCorr;

    if(pElem->pAnt != NULL) {
        pElem->pAnt->pProx = pElem->pProx;
        pLista->pElemCorr = pElem->pAnt;
    }
    else {
        pLista->pElemCorr = pElem->pProx;
        pLista->pOrigemLista = pLista->pElemCorr;
    }

    if(pElem->pProx != NULL)
        pElem->pProx->pAnt = pElem->pAnt;
    else
        pLista->pFimLista = pElem->pAnt;

    LiberarElemento(pLista , pElem);
    return LIS_CondRetOK;
}

void * LIS_ObterValor(LIS_tppLista pLista)
{
#ifdef _DEBUG
    assert(pLista != NULL);
#endif

    if(pLista->pElemCorr == NULL)
        return NULL;
    return pLista->pElemCorr->pValor;
}

LIS_tpCondRet LIS_SetarValor(LIS_tppLista pLista, void *pValor)
{
#ifdef _DEBUG
    assert(pLista != NULL);
#endif

    if(pLista->pElemCorr == NULL)
        return LIS_CondRetListaVazia;
    pLista->pElemCorr->pValor = pValor;
    return LIS_CondRetOK;
}

void LIS_IrInicioLista(LIS_tppLista pLista)
{
#ifdef _DEBUG
    assert(pLista != NULL);
#endif

    pLista->pElemCorr = pLista->pOrigemLista;
}

void LIS_IrFinalLista(LIS_tppLista pLista)
{
#ifdef _DEBUG
    assert(pLista != NULL);
#endif

    pLista->pElemCorr = pLista->pFimLista;
}

LIS_tpCondRet LIS_IrIndice(LIS_tppLista pLista, int i)
{
#ifdef _DEBUG
    assert(pLista != NULL);
#endif

    LIS_IrInicioLista(pLista);
    return LIS_AvancarElementoCorrente(pLista, i);
}

LIS_tpCondRet LIS_AvancarElementoCorrente(LIS_tppLista pLista , int numElem)
{
    int i;

    tpElemLista * pElem;

#ifdef _DEBUG
    assert(pLista != NULL);
#endif

    if(pLista->pElemCorr == NULL)
        return LIS_CondRetListaVazia;

    if(numElem > 0) {
        pElem = pLista->pElemCorr;
        for(i = numElem; i > 0; i--) {
            if(pElem == NULL)
                break;
            pElem = pElem->pProx;
        }

        if(pElem != NULL) {
            pLista->pElemCorr = pElem;
            return LIS_CondRetOK;
        }

        pLista->pElemCorr = pLista->pFimLista;
        return LIS_CondRetFimLista;
    }
    else if(numElem < 0) {
        pElem = pLista->pElemCorr;
        for(i = numElem ; i < 0 ; i++) {
            if(pElem == NULL)
                break;
            pElem = pElem->pAnt;
        }

        if(pElem != NULL) {
            pLista->pElemCorr = pElem;
            return LIS_CondRetOK;
        }

        pLista->pElemCorr = pLista->pOrigemLista;
        return LIS_CondRetFimLista;

    }
    return LIS_CondRetOK;
}

LIS_tpCondRet LIS_ProcurarValor(LIS_tppLista pLista , void * pValor)
{
    tpElemLista * pElem;

#ifdef _DEBUG
    assert(pLista != NULL);
#endif

    if(pLista->pElemCorr == NULL)
        return LIS_CondRetListaVazia;

    for(pElem = pLista->pElemCorr; pElem != NULL; pElem = pElem->pProx) {
        if(pElem->pValor == pValor) {
            pLista->pElemCorr = pElem;
            return LIS_CondRetOK;
        }
    }

    return LIS_CondRetNaoAchou;
}

void LiberarElemento(LIS_tppLista pLista , tpElemLista *pElem)
{
    if((pLista->ExcluirValor != NULL) && (pElem->pValor != NULL))
        pLista->ExcluirValor(pElem->pValor);

    free(pElem);
    pLista->numElem--;
}

tpElemLista * CriarElemento(LIS_tppLista pLista , void * pValor)
{
    tpElemLista * pElem;

    pElem = (tpElemLista *)malloc(sizeof(tpElemLista));
    if(pElem == NULL)
        return NULL;

    pElem->pValor = pValor;
    pElem->pAnt = NULL;
    pElem->pProx = NULL;
    pLista->numElem++;
    return pElem;

}
void LimparCabeca(LIS_tppLista pLista)
{
    pLista->pOrigemLista = NULL;
    pLista->pFimLista = NULL;
    pLista->pElemCorr = NULL;
    pLista->numElem = 0;
}
