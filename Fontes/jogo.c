/*
 * Henrique Santiago
 * Marcelo Resende
 * Rafael Haeusler
*/

#include <stdio.h>
#include <stdlib.h>
#include "tabuleiro.h"
#include "jogo.h"

// classe
typedef struct _Jogo {
    Tabuleiro *tabuleiro;
    int rodando;
    void (*stateFunction)(Jogo *jogo);
} Jogo;

// funcoes privadas
void mainMenu(Jogo *jogo);

// funcoes publicas
Jogo *JOG_criar()
{
    Jogo *jogo = (Jogo*)malloc(sizeof(Jogo));
    if(!jogo)
        return NULL;

    jogo->tabuleiro = TAB_criar();
    if(!jogo->tabuleiro) {
        free(jogo);
        return NULL;
    }

    jogo->stateFunction = mainMenu;
    jogo->rodando = 1;

    return jogo;
}

JOG_tpCondRet JOG_destruir(Jogo *jogo)
{
    if(!jogo)
        return JOG_CondRetJogoInexistente;

    free(jogo);
    return JOG_CondRetOK;
}

void play(Jogo *jogo)
{
    int linhaDe, linhaPara;
    char colunaDe, colunaPara;
    char idJogador[2] = {'x', 'o'};
    int jogadorAtual = 0;
    TAB_inicializar(jogo->tabuleiro, idJogador[0], idJogador[1]);

    int vencedor;
    do { // not finished, check movements, pieces, etc
        TAB_imprimir(jogo->tabuleiro);

        printf("Vez do jogador %c.\n", idJogador[jogadorAtual]);
        printf("Entre com a linha da peca: ");
        scanf("%d", &linhaDe);
        printf("Entre com a coluna da peca: ");
        scanf(" %c", &colunaDe);

        // verificar casa inicial valida ou exibir msg erro

        printf("Entre com a linha de destino: ");
        scanf("%d", &linhaPara);
        printf("Entre com a coluna de destino: ");
        scanf(" %c", &colunaPara);

        // verificar casa final valida ou exibir msg erro

        int ret = TAB_mover(jogo->tabuleiro, linhaDe, colunaDe, linhaPara, colunaPara, idJogador[jogadorAtual]);
        printf("Ret: %d\n", ret);
        // exibe msgs de erro para o jogador

        jogadorAtual = !jogadorAtual;
    } while((vencedor = TAB_verificaVencedor(jogo->tabuleiro, idJogador[0], idJogador[1])) == 0);

    printf("O jogador %c venceu!", idJogador[vencedor-1]);
}

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
}

void JOG_rodar(Jogo *jogo)
{
    while(jogo->stateFunction)
        jogo->stateFunction(jogo);
}
