/*
 * Henrique Santiago
 * Marcelo Resende
 * Rafael Haeusler
*/

#include    <string.h>
#include    <stdio.h>
#include    <malloc.h>

#include    <autotest/tst_espc.h>
#include    <autotest/generico.h>
#include    <autotest/lerparm.h>

#include    "tabuleiro.h"

static const char RESET_TABULEIRO_CMD      [] = "=resetteste";
static const char CRIAR_TABULEIRO_CMD      [] = "=criartabuleiro";
static const char DESTRUIR_TABULEIRO_CMD   [] = "=destruirtabuleiro";
static const char INICIALIZAR_TABULEIRO_CMD[] = "=inicializartabuleiro";
static const char OBTER_PECA_CMD           [] = "=obterpeca";

#define TRUE  1
#define FALSE 0

#define VAZIO     0
#define NAO_VAZIO 1

#define DIM_VT_TABULEIRO   10
#define DIM_VALOR     100

Tabuleiro *vtTabuleiros[DIM_VT_TABULEIRO];

/***** Protótipos das funções encapuladas no módulo *****/

static int ValidarInxTabuleiro(int inxLista, int Modo);

/*****  Código das funções exportadas pelo módulo  *****/


/***********************************************************************
*
*  $FC Função: TLIS &Testar tabuleiro
*
*  $ED Descrição da função
*     Podem ser criadas até 10 tabuleiros, identificados pelos índices 0 a 9
*
*     Comandos disponíveis:
*
*     =resetteste
*           - anula o vetor de pecas. Provoca vazamento de memória
*     =criartabuleiro
*     =destruirtabuleiro         inxLista
*     =inicializartabuleiro      inxLista
*     =obterpeca                 inxLista linha coluna ret
*
***********************************************************************/

TST_tpCondRet TST_EfetuarComando(char *ComandoTeste)
{
    int inxLista  = -1;
    int numLidos   = -1;
    int CondRetEsp = -1;
    void *retPtr;
    char StringDado[DIM_VALOR];
    int i;
    int linha = -1;
    char coluna = -1;
    StringDado[0] = 0;

    if(strcmp(ComandoTeste, RESET_TABULEIRO_CMD) == 0) {
        for(i = 0; i < DIM_VT_TABULEIRO; i++)
            vtTabuleiros[i] = NULL;

        return TST_CondRetOK;
    }
    else if(strcmp(ComandoTeste, CRIAR_TABULEIRO_CMD) == 0) {
        numLidos = LER_LerParametros("i", &inxLista);

        if((numLidos != 1) || (!ValidarInxTabuleiro(inxLista, VAZIO)))
            return TST_CondRetParm;

        vtTabuleiros[inxLista] = TAB_criar();
        return TST_CompararPonteiroNulo(1, vtTabuleiros[inxLista], "Erro em ponteiro do novo tabuleiro.");
    }
    else if(strcmp(ComandoTeste, DESTRUIR_TABULEIRO_CMD) == 0) {
        numLidos = LER_LerParametros("i", &inxLista);

        if((numLidos != 1) || (!ValidarInxTabuleiro(inxLista, NAO_VAZIO)))
            return TST_CondRetParm;

        TAB_destruir(vtTabuleiros[inxLista]);
        vtTabuleiros[inxLista] = NULL;

        return TST_CondRetOK;
    }
    else if(strcmp(ComandoTeste, INICIALIZAR_TABULEIRO_CMD) == 0) {
        numLidos = LER_LerParametros("i", &inxLista);

        if((numLidos != 1) || (!ValidarInxTabuleiro(inxLista, NAO_VAZIO)))
            return TST_CondRetParm;

        TAB_inicializar(vtTabuleiros[inxLista]);
        return TST_CondRetOK;
    }
    else if(strcmp(ComandoTeste, OBTER_PECA_CMD) == 0) {
        numLidos = LER_LerParametros("iisi", &inxLista, &linha, StringDado, &CondRetEsp);

        if((numLidos != 4) || (!ValidarInxTabuleiro(inxLista, NAO_VAZIO)))
            return TST_CondRetParm;

        coluna = StringDado[0];
        retPtr = (void*)TAB_obterPeca(vtTabuleiros[inxLista], linha, coluna);
        return TST_CompararPonteiroNulo(CondRetEsp, retPtr, "Valor não deveria existir.");
    }

    return TST_CondRetNaoConhec;
}

/*****  Código das funções encapsuladas no módulo  *****/

/***********************************************************************
*
*  $FC Função: TLIS -Validar indice de peca
*
***********************************************************************/

int ValidarInxTabuleiro(int inxLista, int Modo)
{
    if((inxLista <  0) || (inxLista >= DIM_VT_TABULEIRO))
        return FALSE;

    if(Modo == VAZIO) {
        if(vtTabuleiros[inxLista] != 0)
            return FALSE;
    } else {
        if(vtTabuleiros[inxLista] == 0)
            return FALSE;
    }
    return TRUE;
}
