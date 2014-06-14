
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
*
***********************************************************************/
typedef struct _Jogo {
    Tabuleiro *tabuleiro;
    int rodando;
    void (*stateFunction)(Jogo *jogo);
} Jogo;

/***** Protótipos das funções encapsuladas no módulo *****/
void mainMenu(Jogo *jogo);
void play(Jogo *jogo);


/*****  Código das funções exportadas pelo módulo  *****/

/***************************************************************************
*
*  Função: JOG  &Criar jogo
*  ****/
Jogo *JOG_criar()
{
    Jogo *jogo = (Jogo*)malloc(sizeof(Jogo));
    if(!jogo)
        return NULL;

#ifdef _DEBUG
    CED_DefinirTipoEspaco(jogo, JOG_Jogo);
#endif

    jogo->tabuleiro = TAB_criar();
    if(!jogo->tabuleiro) {
        free(jogo);
        return NULL;
    }

    jogo->stateFunction = mainMenu;
    jogo->rodando = 1;

    return jogo;
}/* Fim função: JOG  &Criar jogo */


/***************************************************************************
*
*  Função: JOG  &Destruir jogo
*  ****/
JOG_tpCondRet JOG_destruir(Jogo *jogo)
{
    if(!jogo)
        return JOG_CondRetJogoInexistente;

    free(jogo);
    return JOG_CondRetOK;
}/* Fim função: JOG  &Destruir jogo */


/***************************************************************************
*
*  Função: JOG  &Atestar andamento do jogo
*  ****/
void JOG_rodar(Jogo *jogo)
{
    while(jogo->stateFunction)
        jogo->stateFunction(jogo);
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
*       especificações de jogo detalhadas em 'especificacao.pdf'
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
void play(Jogo *jogo)
{
    int linhaDe, linhaPara;
    char colunaDe, colunaPara;
    char idJogador[2] = {'x', 'o'};
    int jogadorAtual = 0;
    int vencedor;
    Peca *pecaDe, *pecaPara;
    PecaTipo tipo;
    TAB_inicializar(jogo->tabuleiro, idJogador[0], idJogador[1]);

    do { // not finished, check movements, pieces, etc
        TAB_imprimir(jogo->tabuleiro);

        printf("Vez do jogador %c.\n", idJogador[jogadorAtual]);
        printf("Entre com a linha da peca: ");
        scanf("%d", &linhaDe);
        printf("Entre com a coluna da peca: ");
        scanf(" %c", &colunaDe);

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

        if(linhaPara < 1 || linhaPara > 8) {
            printf("Linha de destino invalida. Tente novamente.\n");
            continue;
        }

        printf("Entre com a coluna de destino: ");
        scanf(" %c", &colunaPara);

        colunaPara = tolower(colunaPara);
        if(colunaPara < 'a' || colunaPara > 'h') {
            printf("Coluna de destino invalida. Tente novamente.\n");
            continue;
        }

        tipo = PEC_obterTipo(pecaDe);
        if(tipo == PecaNormal) {
            // jogador0 vai para cima, jogador 1 vai para baixo
            int direcao = jogadorAtual == 0 ? 1 : -1;

        }
        else if(tipo == PecaDama) {
            // pode mover para cima e baixo
        }

        pecaPara = TAB_obterCasa(jogo->tabuleiro, linhaPara, colunaPara);
        if(pecaPara) {
            printf("Ja existe uma peca nessa posicao. Tente novamente.\n");
            continue;
        }

        TAB_setarCasa(jogo->tabuleiro, linhaDe, colunaDe, NULL);
        TAB_setarCasa(jogo->tabuleiro, linhaPara, colunaPara, pecaDe);

        jogadorAtual = !jogadorAtual;
    } while((vencedor = TAB_verificaVencedor(jogo->tabuleiro, idJogador[0], idJogador[1])) == 0);

    printf("O jogador %c venceu!", idJogador[vencedor-1]);
    jogo->stateFunction = mainMenu;
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
void mainMenu(Jogo *jogo)
{
    int opcao;
    printf("1 - Iniciar novo jogo\n");
    printf("2 - Sair\n");
    printf("Escolha a opcao desejada: ");
    scanf("%d", &opcao);

    switch(opcao) {
    case 1:
        jogo->stateFunction = play;
        break;
    case 2:
        jogo->stateFunction = NULL;
        break;
    default:
        printf("Opcao invalida. Tente novamente.\n");
        break;
    }
}/* Fim função: JOG  &Jogar jogo */
