
/***************************************************************************
*  $MCI Módulo de implementação: JOG  Jogo 
*
*  Arquivo gerado:              JOGO.c
*  Letras identificadoras:      JOG
*
*  Projeto: damas
*  Arquivo: damas\Fontes\jogo.c    
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
*    programas redigidos em C;
*  
***************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "tabuleiro.h"
#include "peca.h"
#include "jogo.h"

#ifdef _DEBUG
#include "generico.h"
#include "conta.h"
#include "cespdin.h"
#include "tipos.h"
#endif

/***********************************************************************
*
*  $TC Tipo de dados: JOG estrutura de jogo.
*
***********************************************************************/
typedef struct _Jogo {
    Tabuleiro *tabuleiro;
    void (*funcaoEstado)(Jogo *jogo);
} Jogo;

/***** Protótipos das funções encapsuladas no módulo *****/
JOG_tpCondRet menu(Jogo *jogo);
JOG_tpCondRet jogar(Jogo *jogo);


/*****  Código das funções exportadas pelo módulo  *****/

/***************************************************************************
*
*  Função: JOG  &Criar jogo
*  ****/
Jogo *JOG_criar()
{
    Jogo *jogo = (Jogo*)malloc(sizeof(Jogo));
    //Tratamento de exceção
#ifdef _DEBUG
    if(!jogo)
      printf("Problema na alocação de memoria para o jogo");
      return NULL;
#endif
      //Tratamento de espaço dinamico
#ifdef _DEBUG
    CED_DefinirTipoEspaco(jogo, JOG_Jogo);
#endif

#ifdef _DEBUG
    CED_DefinirTipoEspaco(jogo, JOG_Jogo);
#endif

    jogo->tabuleiro = TAB_criar();
    
    //Assertiva de saida
#ifdef _DEBUG
    if(!jogo->tabuleiro) {
        free(jogo);
        return NULL;
    }
#endif

    jogo->funcaoEstado = menu;

    return jogo;
}/* Fim função: JOG  &Criar jogo */


/***************************************************************************
*
*  Função: JOG  &Destruir jogo
*  ****/
JOG_tpCondRet JOG_destruir(Jogo *jogo)
{
    //Assertiva de entrada
#ifdef _DEBUG  
  if(!jogo)
        return JOG_CondRetJogoInexistente;
#endif

    TAB_destruir(jogo->tabuleiro);
    free(jogo);
    return JOG_CondRetOK;
}/* Fim função: JOG  &Destruir jogo */


/***************************************************************************
*
*  Função: JOG  &Atestar andamento do jogo
*  ****/
JOG_tpCondRet JOG_rodar(Jogo *jogo)
{
  //Assertivas de entrada
#ifdef _DEBUG
  if(!jogo)
    return JOG_CondRetJogoInexistente;
#endif

    while(jogo->funcaoEstado)
        jogo->funcaoEstado(jogo);
}/* Fim função: JOG  &Atestar andamento do jogo */



/*****  Código das funções encapsuladas no módulo  *****/


/***************************************************************************
*
*  $FC Função: JOG  &Jogar jogo
*  $ED Descrição da função
*     
*       Está função é toda encarregada de posicionar as pecas no
*       tabuleiro, identificar se uma determinada movimentação de peça
*       pode ou não ser realizada, principalmente da cargo de todas as
*       especificações de jogo detalhadas em "especificacao.pdf"
*       localizado nos documentos do projeto.
*  
*  $EP Parâmetros
*       $P Jogo *jogo 
*
*  $FV Valor retornado 
*
*                Não há valor retornado, está função recebe
*                coordenadas de jogo e de movimentação e as aplica no
*                tabuleiro, o exibindo (prompt de comando) modificado
*                após a realização de todos os passos.
*		
*
***********************************************************************/
JOG_tpCondRet jogar(Jogo *jogo)
{

    int linhaDe, linhaPara, linhaRemover = -1;
    char colunaDe, colunaPara, colunaRemover = -1;
    char idJogador[2] = {'x', 'o'};
    int jogadorAtual = 0;
    int vencedor = -1;
	int distX, distY;
    Peca *pecaDe = NULL, *pecaPara = NULL, *pecaRemover = NULL;

    PecaTipo tipo;

  //Assertivas de entrada
#ifdef _DEBUG
  if(!jogo)
    return JOG_CondRetJogoInexistente;
  if(!jogo->tabuleiro)
    return JOG_CondRetTabuleiroInexistente;
#endif


    TAB_inicializar(jogo->tabuleiro, idJogador[0], idJogador[1]);

    do {
        TAB_imprimir(jogo->tabuleiro);

        printf("Vez do jogador %c.\n", idJogador[jogadorAtual]);
        printf("Entre com a linha da peca: ");
        scanf("%d", &linhaDe);
        //Tratamento de exceção
#ifdef _DEBUG
	if(linhaDe == NULL || linhaDe > 8 || linhaDe < 1){
	  printf("Linha fora dos limites do tabuleiro");
	  continue;
	}
#endif

        printf("Entre com a coluna da peca: ");
        scanf(" %c", &colunaDe);
	//Tratamento de exceção
#ifdef _DEBUG
	if(colunaDe== NULL || tolower(colunaDe) < 'a' || tolower(colunaDe) > 'h'){
	  printf("Coluna fora dos limites do tabuleiro");
	  continue;
	}
#endif

        colunaDe = tolower(colunaDe);

        pecaDe = TAB_obterCasa(jogo->tabuleiro, linhaDe, colunaDe);
        if(!pecaDe) {
            printf("Nao ha nenhuma peca nessa posicao. Tente novamente.\n");
            continue;
        }

        if(PEC_obterCaracter(pecaDe) != idJogador[jogadorAtual]) {
            printf("Essa peca pertence a outro jogador. Tente novamente.\n");
            continue;
        }

        printf("Entre com a linha de destino: ");
        scanf("%d", &linhaPara);
        //Tratamento de exceção
#ifdef _DEBUG
	if(linhaPara == NULL || linhaPara > 8 || linhaPara < 1){
	  printf("Linha fora dos limites do tabuleiro");
	  
	}
#endif

        if(linhaPara < 1 || linhaPara > 8) {
            printf("Linha de destino invalida. Tente novamente.\n");
            continue;
        }

        tipo = PEC_obterTipo(pecaDe);
        if(tipo == PecaNormal) {
            // jogador0 vai para cima, jogador 1 vai para baixo
            int direcao = jogadorAtual == 0 ? 1 : -1;
            if((linhaPara - linhaDe) * direcao <= 0) {
                printf("Direcao de movimento invalida. Tente novamente.\n");
                continue;
            }
        }

        printf("Entre com a coluna de destino: ");
        scanf(" %c", &colunaPara);
	//Tratamento de exceção
#ifdef _DEBUG
	if(colunaPara == NULL || tolower(colunaPara) < 'a' || tolower(colunaPara) > 'h'){
	  printf("Coluna fora dos limites do tabuleiro");

	}
#endif

        colunaPara = tolower(colunaPara);
        if(colunaPara < 'a' || colunaPara > 'h' ) {
            printf("Coluna de destino invalida. Tente novamente.\n");
            continue;
        }

        pecaPara = TAB_obterCasa(jogo->tabuleiro, linhaPara, colunaPara);
        if(pecaPara) {
            printf("Ja existe uma peca nessa posicao. Tente novamente.\n");
            continue;
        }

        distX = abs(colunaPara - colunaDe);
        if(distX == 0) {
            printf("A peca se move nas diagonais. Tente novamente.\n");
            continue;
        }

        distY = abs(linhaPara - linhaDe);
        if(distX > 2 || distY > 2) {
            printf("Movimento muito distante. Tente novamente.\n");
            continue;
        }

        if(distX == 2 && distY == 2) {
            linhaRemover = (linhaPara + linhaDe) / 2;
            colunaRemover = (colunaPara + colunaDe) / 2;
            pecaRemover = TAB_obterCasa(jogo->tabuleiro, linhaRemover, colunaRemover);
            if(!pecaRemover) {
                printf("Movimento muito distante sem peca para comer. Tente novamente.\n");
                linhaRemover = -1;
                colunaRemover = -1;
                continue;
            }
            else if(PEC_obterCaracter(pecaRemover) == idJogador[jogadorAtual]) {
                printf("Voce nao pode comer sua propria peca. Tente novamente.\n");
                linhaRemover = -1;
                colunaRemover = -1;
                continue;
            }
        }
        else if(distX != 1 || distY != 1) {
            printf("Movimento invalido. Tente novamente.\n");
            continue;
        }

        TAB_setarCasa(jogo->tabuleiro, linhaDe, colunaDe, NULL, 0);
        TAB_setarCasa(jogo->tabuleiro, linhaPara, colunaPara, pecaDe, 0);

        if(linhaRemover != -1 && colunaRemover != -1) {
            TAB_setarCasa(jogo->tabuleiro, linhaRemover, colunaRemover, NULL, 1);
            linhaRemover = -1;
            colunaRemover = -1;
        }

        if(tipo == PecaNormal && ((jogadorAtual == 0 && linhaPara == 8) || (jogadorAtual == 1 && linhaPara == 1))) {
            PEC_setarTipo(pecaDe, PecaDama);
            printf("A peca do jogador %c virou DAMA.\n", idJogador[jogadorAtual]);
        }

        jogadorAtual = !jogadorAtual;
    } while((vencedor = TAB_verificaVencedor(jogo->tabuleiro, idJogador[0], idJogador[1])) == -1);

    printf("O jogador %c venceu!\n", idJogador[vencedor]);
    jogo->funcaoEstado = menu;
}/* Fim função: JOG  &Jogar jogo */

/***************************************************************************
*
*  $FC Função: JOG  &Jogar jogo
*  $ED Descrição da função
*     
*       Está função apenas introduz ao usuário suas opções de jogo, é
*       encarregado pelo menu de jogo, da mais jogabilidade ao
*       projeto.
*  
*  $EP Parâmetros
*       $P Jogo *jogo 
*
*  $FV Valor retornado 
*
*                Não há valor retornado, apenas imprimi na tela as
*                opções que o jogador tem ao executar o programa,
*                (iniciar jogo ou sair).
*
***********************************************************************/
JOG_tpCondRet menu(Jogo *jogo)
{

     int opcao;

  //Assertivas de entrada
#ifdef _DEBUG
  if(!jogo)
    return  JOG_CondRetJogoInexistente;
  if(!jogo->tabuleiro)
    return JOG_CondRetTabuleiroInexistente;
#endif


 
    printf("1 - Iniciar novo jogo\n");
    printf("2 - Sair\n");
    printf("Escolha a opcao desejada: ");
    scanf("%d", &opcao);
    //Tratamento de excecao
#ifdef _DEBUG
    while(opcao != 1 || opcao != 2){
      printf("\n Opção inválida \n");
      printf("1 - Iniciar novo jogo\n");
      printf("2 - Sair\n");
      printf("Escolha a opcao desejada: ");
      scanf("%d", &opcao);
    }
#endif 
    switch(opcao) {
    case 1:
        jogo->funcaoEstado = jogar;
        break;
    case 2:
        jogo->funcaoEstado = NULL;
        break;
    }
}/* Fim função: JOG  &Jogar jogo */
