/***************************************************************************
*  $MCI Módulo de implementação: PEC  Peca 
*
*  Arquivo gerado:              PECA.c
*  Letras identificadoras:      PEC
*
*  Projeto: damas
*  Arquivo: damas\Fontes\peca.c    
*
*  Autores: hs - Henrique Santiago
*	    mr - Marcelo Resende
*	    rh - Rafael Haeusler
*  
*  $HA Histórico de evolução: 
*     Versão  Autor    Data     Observações
*     2       hs/mr/rh   17/junho/2014    implementação completa do jogo
*  
*  $CRE Créditos
*    Arndt von Staa. Programa AutoTest - Arcabouço para a automação de testes de 
*    programas redigidos em C;módulo Lista Duplamente Encadeada
*  
***************************************************************************/

#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#define peca_OWN
#include "peca.h"
#undef peca_OWN

#ifdef _DEBUG
#include "generico.h"
#include "conta.h"
#include "cespdin.h"
#include "tipos.h"
#endif

/***********************************************************************
*
*  $TC Tipo de dados: PEC tipo estipula a estrutura de peca
*
*
***********************************************************************/
typedef struct _Peca {
    PecaTipo tipo;
    char caracter;
} Peca;


/*****  Código das funções exportadas pelo módulo  *****/

/***************************************************************************
*
*  Função: PEC  &Criar uma peça
*  ****/
Peca *PEC_criar(PecaTipo tipo, char caracter)
{
    Peca *peca = (Peca*)malloc(sizeof(Peca));
    //Assertivas de entrada
#ifdef _DEBUG    
    if( tipo != PecaNormal && tipo != PecaDama)
      printf("\n Tipo da peca não condiz com qualquer tipo existente (PEC_criar) \n");    
    
#endif

    //Tratamento de espaço dinamico
#ifdef _DEBUG
    CED_DefinirTipoEspaco(peca, PEC_Peca);
#endif
    
    if(peca == NULL)
      return NULL;

    PEC_setarTipo(peca, tipo);
    PEC_setarCaracter(peca, tolower(caracter));
    //Assertiva de saída
#ifdef _DEBUG
    if(peca->caracter != caracter)
      printf("\n A criação da peça não atribuiu o valor correto do caracter \n");
    if(peca->tipo != tipo)
      printf("\n A criação da peça não atribuiu o valor correto de tipo \n");
    if(!peca)
      printf("\n Não foi possível alocar memoria para peca (PEC_criar) \n");
#endif


    return peca;
}/* Fim função: PEC  &Criar uma peça */


/***************************************************************************
*
*  Função: PEC  &Destruir uma determinada peça
*  ****/
PEC_tpCondRet PEC_destruir(Peca *peca)
{
  //Assertva de entrada
#ifdef _DEBUG 
  if(!peca)
    return PEC_CondRetPecaVazia;
#endif

    free(peca);
    return PEC_CondRetOK;
}/* Fim função: PEC  &Destruir uma determinada peça */


/***************************************************************************
*
*  Função: PEC  &Imprimir uma determinada  peça
*  ****/
void PEC_imprimir(Peca *peca)
{
  //Assertiva de entrada
#ifdef _DEBUG
  if(peca->PecaTipo == PecaErro)
    printf("\n peca vazia (PEC_imprimir) \n");
#endif
    if(peca->tipo == PecaNormal)
        printf("%c|", peca->caracter);
    else
        printf("%c|", toupper(peca->caracter));
}/* Fim função: PEC  &Imprimir uma determinada peça */


/***************************************************************************
*
*  Função: PEC  &Obter tipo de uma determinada  peça
*  ****/
PecaTipo PEC_obterTipo(Peca *peca)
{
  //Assertivas de entrada
#ifdef _DEBUG
  if(peca->Pecatipo == PecaErro){
    printf("peca vazia (PEC_imprimir)");
    return ;
  }
  if( peca->tipo != PecaNormal && peca->tipo != PecaDama){
    printf("\n Tipo da peca não condiz com qualquer tipo existente (PEC_obterTipo) \n");    
    return;
  }
#endif

    return peca->tipo;
}/* Fim função: PEC  &Obter tipo de uma determinada peça */


/***************************************************************************
*
*  Função: PEC  &Setar tipo de uma determinada  peça
*  ****/
PEC_tpCondRet PEC_setarTipo(Peca *peca, PecaTipo tipo)
{
  //Assertivas de entrada
#ifdef _DEBUG
  if(peca->PecaTipo == PecaErro)
    return PEC_CondRetPecaVazia;
    
  if( tipo != PecaNormal && tipo != PecaDama)
    return PEC_CondRetTipoInexistente;
#endif

    peca->tipo = tipo;
    //Assetivas de saida
#ifdef _DEBUG
    if(peca->tipo != PecaNormal && peca->tipo != PecaDama)
      return PEC_CondRetTipoInexistente;
#endif

    return PEC_CondRetOK;
}/* Fim função: PEC  &Setar tipo de uma determinada peça */


/***************************************************************************
*
*  Função: PEC  &Obter caracter identificador de uma determinada  peça
*  ****/
char PEC_obterCaracter(Peca *peca)
{
  //Assertivas de entrada
#ifdef _DEBUG
  if(peca->PecaTipo == PecaErro){
    printf("\n peca vazia (PEC_obterCaracter) \n");
    return NULL;
  }
#endif

    return peca->caracter;
}/* Fim função: PEC  &Obter caracter identificador de uma determinada peça */


/***************************************************************************
*
*  Função: PEC  &Setar caracter identificador de uma determinada  peça
*  ****/
PEC_tpCondRet PEC_setarCaracter(Peca *peca, char caracter)
{
  //Assertivas de entrada
#ifdef _DEBUG
  if(peca->PecaTipo == PecaErro)
    return PEC_CondRetPecaVazia;
    
#endif

    caracter = tolower(caracter);
    peca->caracter = caracter;
    //Assetivas de saida
#ifdef _DEBUG
    if(peca->caracter != caracter && peca->caracter != caracter)
      return PEC_CondRetCaracterInexistente;
#endif

    return PEC_CondRetOK;
}/* Fim função: PEC  &Setar caracter identificador de uma determinada  peça */

/********** Fim do módulo de definição: PEC Peca **********/
