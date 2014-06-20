
/***************************************************************************
*  $MCI Módulo de implementação: TAB  Tabuleiro 
*
*  Arquivo gerado:              TABULEIRO.c
*  Letras identificadoras:      TAB
*
*  Projeto: damas
*  Arquivo: damas\Fontes\tabuleiro.c    
*
*  Autores: hs - Henrique Santiago
*	    mr - Marcelo Resende
*	    rh - Rafael Haeusler
*  
*  $HA Histórico de evolução: 
*     Versão  Autor    Data     Observações
*      2       hs/mr/rh   17/junho/2014    implementação completa do jogo
*  
*  $CRE Créditos
*    Arndt von Staa. Programa AutoTest - Arcabouço para a automação de testes de 
*    programas redigidos em C;
*  
***************************************************************************/

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define tabuleiro_OWN   
#include "tabuleiro.h"
#undef tabuleiro_OWN 

#include "lista.h"
#include "peca.h"

#ifdef _DEBUG
#include "generico.h"
#include "conta.h"
#include "cespdin.h"
#include "tipos.h"
#endif

/* Define as dimensões do tabuleiro */
enum {
    TabuleiroAltura = 8,
    TabuleiroLargura = 8,
};

/***********************************************************************
*
*  $TC Tipo de dados: TAB estrutura que referencia uma lista
*  duplamente encadeada que representa as linhas do tabuleiro 
*
*
***********************************************************************/
typedef struct _Tabuleiro {
    LIS_tppLista lista;
} Tabuleiro;

/***** Protótipos das funções encapsuladas no módulo *****/
static void ListaExcluirPeca(void *pDado);
static void ListaExcluirLista(void *pDado); 

/*****  Código das funções exportadas pelo módulo  *****/
/***************************************************************************
*
*  Função: TAB  &Criar tabuleiro
*  ****/

Tabuleiro *TAB_criar()
{
    int x, y;
    Tabuleiro *tabuleiro = (Tabuleiro*)malloc(sizeof(Tabuleiro));
    if(!tabuleiro)
        return NULL;

#ifdef _DEBUG
    CED_DefinirTipoEspaco(tabuleiro, TAB_Tabuleiro);
#endif

    tabuleiro->lista = LIS_CriarLista(ListaExcluirLista);
    if(!tabuleiro->lista) {
        free(tabuleiro);
        return NULL;
    }
    for(y = 0; y < TabuleiroAltura; ++y) {
        LIS_tppLista lista = LIS_CriarLista(ListaExcluirPeca);
        if(!lista) {
            TAB_destruir(tabuleiro);
            return NULL;
        }
        if(LIS_InserirElementoAntes(tabuleiro->lista, lista) != LIS_CondRetOK) {
            TAB_destruir(tabuleiro);
            return NULL;
        }
        for(x = 0; x < TabuleiroLargura; ++x){
            if(LIS_InserirElementoAntes(lista, NULL) != LIS_CondRetOK) {
                TAB_destruir(tabuleiro);
                return NULL;
            }
        }
    }

    return tabuleiro;
}/* Fim função: TAB  &Criar tabuleiro */

/***************************************************************************
*
*  Função: TAB  &Destruir tabuleiro
*  ****/
TAB_tpCondRet TAB_destruir(Tabuleiro *tabuleiro)
{
    if(!tabuleiro)
        return TAB_CondRetTabuleiroInexistente;
    LIS_DestruirLista(tabuleiro->lista);
    free(tabuleiro);
    return TAB_CondRetOK;
}/* Fim função: TAB  &Destruir tabuleiro */


/***************************************************************************
*
*  Função: TAB  &Inicializar tabuleiro para início de uma partida
*  ****/

void TAB_inicializar(Tabuleiro *tabuleiro, char idJogador1, char idJogador2)
{
    int x, y;
#ifdef _DEBUG
    assert(tabuleiro);
#endif
    LIS_IrInicioLista(tabuleiro->lista);
    for(y = 0; y < TabuleiroAltura; ++y) {
        LIS_tppLista lista = (LIS_tppLista)LIS_ObterValor(tabuleiro->lista);
        LIS_IrInicioLista(lista);
        for(x = 0; x < TabuleiroLargura; ++x) {
            Peca *peca = NULL;
            if(y < 2 && (x + y) % 2 == 1)
                peca = PEC_criar(PecaNormal, idJogador1);
            else if(y > TabuleiroAltura - 3 && (x + y) % 2 == 1)
                peca = PEC_criar(PecaNormal, idJogador2);

            LIS_SetarValor(lista, peca);
            LIS_AvancarElementoCorrente(lista, 1);
        }
        LIS_AvancarElementoCorrente(tabuleiro->lista, 1);
    }
}/* Fim função: TAB  &Inicializar tabuleiro para início de uma partida */

/***************************************************************************
*
*  Função: TAB  &Imprimir estado atual de um tabuleiro
*  ****/
void TAB_imprimir(Tabuleiro *tabuleiro)
{
    int x, y;
#ifdef _DEBUG
    assert(tabuleiro);
#endif

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
}/* Fim função: TAB  &Imprimir estado atual de um tabuleiro */


/***************************************************************************
*
*  Função: TAB  &Obter valor de uma peça no tabuleiro
*  ****/

Peca *TAB_obterCasa(Tabuleiro *tabuleiro, int linha, char coluna)
{
    LIS_tppLista lista;
#ifdef _DEBUG
    assert(tabuleiro);
#endif

    --linha;
    coluna = tolower(coluna) - 'a';

    if(LIS_IrIndice(tabuleiro->lista, linha) != LIS_CondRetOK)
        return NULL;
    lista = (LIS_tppLista)LIS_ObterValor(tabuleiro->lista);
    if(!lista)
        return NULL;
    if(LIS_IrIndice(lista, coluna) != LIS_CondRetOK)
        return NULL;
    return LIS_ObterValor(lista);
}/* Fim função: TAB  &Obter valor de uma peça no tabuleiro */

/***************************************************************************
*
*  Função: TAB  &Setar valor de uma peça no tabuleiro
*  ****/

TAB_tpCondRet TAB_setarCasa(Tabuleiro *tabuleiro, int linha, char coluna, Peca *peca, int limpar)
{
    LIS_tppLista lista;
    Peca *antiga;

    if(tabuleiro == NULL)
        return TAB_CondRetTabuleiroInexistente;
    --linha;
    coluna = tolower(coluna) - 'a';

    if(LIS_IrIndice(tabuleiro->lista, linha) != LIS_CondRetOK)
        return TAB_CondRetLinhaInexistente;
    lista = (LIS_tppLista)LIS_ObterValor(tabuleiro->lista);
    if(!lista)
        return TAB_CondRetLinhaInexistente;
    
    if(LIS_IrIndice(lista, coluna) != LIS_CondRetOK)
        return TAB_CondRetColunaInexistente;

    if(limpar) {
        antiga = LIS_ObterValor(lista);
        if(antiga)
            ListaExcluirPeca(antiga);
    }

    LIS_SetarValor(lista, peca);
    return TAB_CondRetOK;
}/* Fim função: TAB  &Setar valor de uma peça no tabuleiro */

/***************************************************************************
*
*  Função: TAB  &mover uma peça no tabuleiro
*  ****/
int TAB_verificaVencedor(Tabuleiro *tabuleiro, char idJogador1, char idJogador2)
{
    int x, y;
    int existe1 = 0, existe2 = 0;
    assert(tabuleiro);
    LIS_IrFinalLista(tabuleiro->lista);
    for(y = TabuleiroAltura - 1; y >= 0; --y) {
        LIS_tppLista lista = (LIS_tppLista)LIS_ObterValor(tabuleiro->lista);
        LIS_IrInicioLista(lista);
        for(x = 0; x < TabuleiroLargura; ++x) {
            Peca *peca = LIS_ObterValor(lista);
            if(peca) {
                if(PEC_obterCaracter(peca) == idJogador1)
                    existe1 = 1;
                else if(PEC_obterCaracter(peca) == idJogador2)
                    existe2 = 1;

                if(existe1 && existe2) // existe peca dos 2 jogadores no tabuleiro. jogo continua
                    return -1;
            }

            LIS_AvancarElementoCorrente(lista, 1);
        }
        LIS_AvancarElementoCorrente(tabuleiro->lista, -1);
    }

    if(existe1 && !existe2) // so ha pecas do jogador 1 presentes. ele ganhou
        return 0;
    if(!existe1 && existe2) // so ha pecas do jogador 2 presentes. ele ganhou
        return 1;

    assert("Caso indefinido TAB_verificaVencedor");
	return -2;
}/* Fim função: TAB verifica vencedor */


#ifdef _DEBUG

/***************************************************************************
*
*  Função: TAB  &Verificar a estrutura tabuleiro (ista de listas)
*  ****/

TAB_tpCondRet TAB_VerificarTabuleiro(Tabuleiro* tabuleiro)
{
    int condRet;
    if(!tabuleiro) {
        CNT_CONTAR("Tabuleiro Inexistente");
        TST_NotificarFalha("Tentou verificar tabuleiro inexistente.");
        return TAB_CondRetErroEstrutura;
    }
    else
        CNT_CONTAR("Tabuleiro Existente");

    if(!CED_VerificarEspaco(tabuleiro, NULL)) {
        CNT_CONTAR("Tabuleiro possui alguma falha");
        TST_NotificarFalha("Controle do espaço acusou erro.");
        return TAB_CondRetErroEstrutura ;
    }
    else
        CNT_CONTAR("Tabuleiro nao possui falha");

    if(TST_CompararInt(TAB_Tabuleiro, CED_ObterTipoEspaco(tabuleiro),
                       "Tipo do espaço de dados nao e tabuleiro.") != TST_CondRetOK) {
        CNT_CONTAR("Tipo nao e Tabuleiro");
        return TAB_CondRetErroEstrutura;
    }
    else
        CNT_CONTAR("Tipo e Tabuleiro");

    CNT_CONTAR("Tipo Tabuleiro OK");
    condRet = LIS_VerificarLista(tabuleiro->lista);
    return condRet;
}

/***************************************************************************
*
*  Função: TAB  &Deturpar tabuleiro
*  ****/

void TAB_Deturpar(Tabuleiro *tabuleiro, TAB_tpModosDeturpacao ModoDeturpar)
{
    int x, y;
    LIS_tppLista lista, lista2;
    if(!tabuleiro)
        return;

    lista = tabuleiro->lista;

    switch(ModoDeturpar) {
    case TAB_EliminarLinha:
    {
        LIS_ExcluirElemento(lista);
        break;
    }
    case TAB_EliminarPosicao:
    {
        LIS_ExcluirElemento((LIS_tppLista)LIS_ObterValor(lista));
        break;
    }
    case TAB_EliminarPecaSemFree:
    {
        LIS_IrInicioLista(lista);
        for(y = 0; y < TabuleiroAltura; ++y) {
            lista2 = (LIS_tppLista)LIS_ObterValor(lista);
            LIS_IrInicioLista(lista);
            for(x = 0; x < TabuleiroLargura; ++x) {
                Peca *peca = LIS_ObterValor(lista);
                if(peca) {
                    LIS_SetarValor(lista2, NULL);
                    return;
                }
            }
        }
        break;
    }
    case TAB_DeturpaTipoPeca:
    {
        LIS_IrInicioLista(lista);
        for(y = 0; y < TabuleiroAltura; ++y) {
            lista2 = (LIS_tppLista)LIS_ObterValor(lista);
            LIS_IrInicioLista(lista);
            for(x = 0; x < TabuleiroLargura; ++x) {
                Peca *peca = LIS_ObterValor(lista);
                if(peca) {
                    CED_DefinirTipoEspaco(peca, CED_ID_TIPO_VALOR_NULO);
                    return;
                }
            }
        }

        break;
    }
	case TAB_DeturpaTipoTabuleiro:
	{
		CED_DefinirTipoEspaco(tabuleiro, CED_ID_TIPO_VALOR_NULO);
		break;
	}
    }
}
/***************************************************************************
*
*  Função: TAB  &Posicionar Elemento Corrente
*  ****/

void PosicionarElementoCorrente(Tabuleiro *tabuleiro, int linha, char coluna)
{
    LIS_tppLista lista;
    --linha;
    coluna = tolower(coluna) - 'a';

    LIS_IrIndice(tabuleiro->lista, linha);
    lista = (LIS_tppLista)LIS_ObterValor(tabuleiro->lista);
    LIS_IrIndice(lista, coluna) ;
}/* Fim função: TAB  &Posicionar Elemento Corrente */

#endif

/*****  Código das funções encapsuladas no módulo  *****/   

/***************************************************************************
*
*  $FC Função: TAB  -Excluir elemento de uma lista
*
*  $ED Descrição da função
*
*      Através da função (PEC_destruir(Peca *peca)) provida pelo
*      módulo PEC (peça), está função elimina uma peça do tabuleiro
*      
*  $EP Parâmetros 
*
*      $P void *pDado - um ponteiro para um tipo void (qualquer).
*      
*
*  $FV Valor retornado 
*
*        Não possui valor de retorno, simplesmente elimina (free())
*        uma peça do tabuleiro.
*
*  ****/
void ListaExcluirPeca(void *pDado)                           
{                                                             
    Peca *peca = (Peca*)pDado;
    PEC_destruir(peca);
}/* Fim função: TAB  -Excluir elemento de uma lista */

/***************************************************************************
*
*  $FC Função: TAB  -Excluir uma lista
*
*  $ED Descrição da função
*
*      Através da função (LIS_DestruirLista(LIS_tppLista lista))
*      provida pelo módulo LIS (lista), está função elimina linha do
*      tabuleiro.
*      
*  $EP Parâmetros 
*
*      $P void *pDado - um ponteiro para um tipo void (qualquer).
*      
*
*  $FV Valor retornado 
*
*        Não possui valor de retorno, simplesmente elimina (free())
*        uma linha do tabuleiro.
*
*  ****/
void ListaExcluirLista(void *pDado)                         
{
    LIS_tppLista lista = (LIS_tppLista)pDado;
    LIS_DestruirLista(lista);
}/* Fim função: TAB  -Excluindo uma lista */ 

/********** Fim do módulo de implementação: TAB  Tabuleiro **********/
