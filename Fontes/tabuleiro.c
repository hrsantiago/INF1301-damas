
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
*     1       hs/mr/rh   30/abril/2014    implementação parcial do jogo
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
    if(tabuleiro == NULL)
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

TAB_tpCondRet TAB_setarCasa(Tabuleiro *tabuleiro, int linha, char coluna, Peca *peca)
{
    LIS_tppLista lista;
//    Peca *antiga;

    if(tabuleiro == NULL)
        return TAB_CondRetTabuleiroInexistente;
    --linha;
    coluna = tolower(coluna) - 'a';

    if(LIS_IrIndice(tabuleiro->lista, linha) != LIS_CondRetOK)
        return TAB_CondRetLinhaInexistente;
    lista = (LIS_tppLista)LIS_ObterValor(tabuleiro->lista);
    /*ver ainda se está certo
    if(!lista)
    return;*/
    
    if(LIS_IrIndice(lista, coluna) != LIS_CondRetOK)
        return TAB_CondRetColunaInexistente;

    // nao limpar peca por hora, somente e utilizada por tab_mover
//    antiga = LIS_ObterValor(lista);
//    if(antiga)
//        ListaExcluirPeca(antiga);

    LIS_SetarValor(lista, peca);
    return TAB_CondRetOK;
}/* Fim função: TAB  &Setar valor de uma peça no tabuleiro */

/***************************************************************************
*
*  Função: TAB  &mover uma peça no tabuleiro
*  ****/

TAB_tpCondRet TAB_mover(Tabuleiro *tabuleiro, int linhaDe, char colunaDe, int linhaPara, char colunaPara, char idJogador)
{
    Peca *peca = TAB_obterCasa(tabuleiro, linhaDe, colunaDe);
    if(!peca)
        return TAB_CondRetPecaInexistente;

    if(PEC_obterCaracter(peca) != idJogador)
        return TAB_CondRetPecaNaoPertenceJogador;

    if(TAB_obterCasa(tabuleiro, linhaPara, colunaPara))
        return TAB_CondRetPosDestOcupada;

    TAB_setarCasa(tabuleiro, linhaDe, colunaDe, NULL);
    TAB_setarCasa(tabuleiro, linhaPara, colunaPara, peca);

    return TAB_CondRetOK;
}/* Fim função: TAB  &mover uma peça no tabuleiro */

/***************************************************************************
*
*  Função: TAB  &mover uma peça no tabuleiro
*  ****/
int TAB_verificaVencedor(Tabuleiro *tabuleiro, char idJogador1, char idJogador2)
{
    assert(tabuleiro);
    int x, y;
    int existe1 = 0, existe2 = 0;
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
                    return 0;
            }

            LIS_AvancarElementoCorrente(lista, 1);
        }
        printf("\n");
        LIS_AvancarElementoCorrente(tabuleiro->lista, -1);
    }

    if(existe1 && !existe2) // so ha pecas do jogador 1 presentes. ele ganhou
        return 1;
    if(!existe1 && existe2) // so ha pecas do jogador 2 presentes. ele ganhou
        return 2;
}/* Fim função: TAB verifica vencedor */

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
