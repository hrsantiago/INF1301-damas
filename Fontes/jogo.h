/***************************************************************************
*  $MCD Módulo de declaração: JOG  Jogo
*
*  Arquivo gerado:              JOGO.h
*  Letras identificadoras:      JOG
*  
*  Projeto: damas
*  Arquivo: damas\fontes\jogo.h
*
*
*  Autores: hs - Henrique Santiago
*	    mr - Marcelo Resende
*	    rh - Rafael Haeusler
*  
*
*  $HA Histórico de evolução: 
*     Versão  Autor    Data     Observações
*      2       hs/mr/rh   17/junho/2014    implementação completa do jogo
*
*  $ED Descrição do módulo
*
*      A implementação deste módulo define todas as ações possíveis em
*      relação ao jogo, como sua inicialização e destruição. Também
*      foi implementado a jogabilidade do jogo de damas neste módulo,
*      é aqui onde são definidos os tipos de movimentações possíveis
*      no tabuleiro, segue as especificações do jogo e como deve
*      funcionar um verdadeiro jogo de damas. Este módulo precisa das
*      definições dos módulos tabuleiro.h e peca.h.
*  
*  $CRE Créditos
*    Arndt von Staa. Programa AutoTest - Arcabouço para a automação de testes de 
*    programas redigidos em C;
*  
***************************************************************************/


#ifndef JOGO_H
#define JOGO_H

/***** Declarações exportadas pelo módulo *****/

/***********************************************************************
*
*  $TC Tipo de dados: JOG Condições de retorno
*
*
*  $ED Descrição do tipo
*     Condições de retorno das funções do jogo
*
***********************************************************************/
typedef enum _JOG_tpCondRet{
    JOG_CondRetOK, /* Concluiu corretamente */
    JOG_CondRetOpcaoInvalida, /* Opcao invalida no menu */
    JOG_CondRetJogoInexistente, /* o jogo não existe */
    JOG_CondRetTabuleiroInexistente, /* o tabuleiro não existe */
} JOG_tpCondRet;


/***********************************************************************
*
*  $TC Tipo de dados: JOG estrutura que referencia a estrutura do
*  tabuleiro de jogo, feito para atestar o funcionamento do jogo.
*
*
***********************************************************************/
typedef struct _Jogo Jogo;

/***********************************************************************
*
*  $FC Função: JOG  &Criar jogo
*
*  $ED Descrição da função
*     
*       Inicializa um jogo de acordo com a desposição do tabuleiro
*       (8x8), levando em consideração a disposição ja definida nas
*       especificações.
*  
*  $EP Parâmetros
*       Não possui parâmetro de entrada 
*
*  $FV Valor retornado 
*
*                O valor retornado é uma estrutura Jogo que possui os
*                campos Tabuleiro( tabuleiro do jogo), e um indicador
*                se o jogo continua rodando. O tipo Tabuleiro dentro
*                de Jogo é exatamente o tabuleiro na condicição
*                inicial de um jogo de damas.
*		
*
***********************************************************************/
Jogo *JOG_criar();


/***********************************************************************
*
*  $FC Função: JOG  &Destruir jogo
*
*  $ED Descrição da função
*     
*       Acaba com um jogo, 'destruindo' o tabuleiro, executa um free()
*       no espaço alocado para Tabuleiro.
*  
*  $EP Parâmetros 
*       $P Jogo *jogo - um ponteiro para jogo (campo que
*       consiste do tabuleiro de jogo)
*
*  $FV Valor retornado 
*
*        retorna JOG_tpCondRetOK, se não houver tabuleiro retorna
*        JOG_tpCondRetJogoInexistente.
*		
*
***********************************************************************/
JOG_tpCondRet JOG_destruir(Jogo *jogo);

/***********************************************************************
*
*  $FC Função: JOG  &Atestar andamento do  jogo
*
*  $ED Descrição da função
*     
*       Função utilizada para manter o jogo rodando. Utilizando da
*       função de estado do jogo para verificar os estados em que o
*       jogo s encontra.
*  
*  $EP Parâmetros 
*       $P Jogo *jogo - um ponteiro para jogo (campo que
*       consiste do tabuleiro de jogo)
*
*  $FV Valor retornado 
*
*        retorna JOG_tpCondRetJogoInexistente, se não houver
*        tabuleiro. Senão não retorna nada.
*		
*
***********************************************************************/
JOG_tpCondRet JOG_rodar(Jogo *jogo);

#endif
