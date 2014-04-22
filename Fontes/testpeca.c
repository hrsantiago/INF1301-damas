
/***************************************************************************
*  $MCI M�dulo de implementa��o: Testpeca  Teste do modulo peca
*
*  Arquivo gerado:              testpeca.c
*  Letras identificadoras:      TPEC
*
*  Nome da base de software:     Arcabou�o para a automa��o de testes de programas redigidos em C ?????????
*  Arquivo da base de software: D:\AUTOTEST\PROJETOS\LISTA.BSW ????????????
*
*  Projeto: INF 1301-Trab02-HMR-Damas
*  Gestor:  LES/DI/PUC-Rio ????????????
*  Autores: Henrique Santiago
*
*
*  $HA Hist�rico de evolu��o:
*     Vers�o  Autor    				Data     Observa��es
*     1       Henrique Santiago   13/abr/2014 in�cio desenvolvimento
*
***************************************************************************/

#include    <string.h>
#include    <stdio.h>
#include    <malloc.h>

#include    <tst_espc.h>
#include    <generico.h>
#include    <lerparm.h>

#include    "peca.h"

static const char RESET_PECA_CMD      [] = "=resetteste";
static const char CRIAR_PECA_CMD      [] = "=criarpeca";
static const char DESTRUIR_PECA_CMD   [] = "=destruirpeca";
static const char OBTER_TIPO_CMD      [] = "=obtertipo";
static const char SETAR_TIPO_CMD      [] = "=setartipo";
static const char OBTER_CARACTER_CMD  [] = "=obtercaracter";
static const char SETAR_CARACTER_CMD  [] = "=setarcaracter";

#define TRUE  1
#define FALSE 0

#define VAZIO     0
#define NAO_VAZIO 1

#define DIM_VT_PECA   10
#define DIM_VALOR     100

Peca *vtTabuleiros[DIM_VT_PECA];

/***** Prot�tipos das fun��es encapuladas no m�dulo *****/

static int ValidarInxTabuleiro(int inxLista, int Modo);

/*****  C�digo das fun��es exportadas pelo m�dulo  *****/


/***********************************************************************
*
*  $FC Fun��o: TPEC &Testar peca
*
*  $ED Descri��o da fun��o
*     Podem ser criadas at� 10 pecas, identificadas pelos �ndices 0 a 9
*
*     Comandos dispon�veis:
*
*     =resetteste
*           - anula o vetor de pecas. Provoca vazamento de mem�ria
*     =criarpeca                   inxLista  int     string
*     =destruirpeca                inxLista
*     =obtertipo                   inxLista  int
*     =setartipo                   inxLista  int
*     =obtercaracter               inxLista  string
*     =setarcaracter               inxLista  string
*
***********************************************************************/

TST_tpCondRet TST_EfetuarComando(char *ComandoTeste)
{
    int inxLista  = -1;
    int numLidos   = -1;
    int CondRetEsp = -1;
    char StringDado[DIM_VALOR];
    int i;
    int tipo = -1;
    char caracter = -1;
    StringDado[0] = 0;

    if(strcmp(ComandoTeste, RESET_PECA_CMD) == 0) {
        for(i = 0; i < DIM_VT_PECA; i++)
            vtTabuleiros[i] = NULL;

        return TST_CondRetOK;
    }
    else if(strcmp(ComandoTeste, CRIAR_PECA_CMD) == 0) {
        numLidos = LER_LerParametros("iis", &inxLista, &tipo, StringDado);

        if((numLidos != 3) || (! ValidarInxTabuleiro(inxLista, VAZIO)))
            return TST_CondRetParm;

        vtTabuleiros[inxLista] = PEC_criar(tipo, StringDado[0]);
        return TST_CompararPonteiroNulo(1, vtTabuleiros[inxLista], "Erro em ponteiro de nova peca.");
    }
    else if(strcmp(ComandoTeste, DESTRUIR_PECA_CMD) == 0) {
        numLidos = LER_LerParametros("i", &inxLista);

        if((numLidos != 1) || (! ValidarInxTabuleiro(inxLista, NAO_VAZIO)))
            return TST_CondRetParm;

        PEC_destruir(vtTabuleiros[inxLista]);
        vtTabuleiros[inxLista] = NULL;

        return TST_CondRetOK;
    }
    else if(strcmp(ComandoTeste, OBTER_TIPO_CMD) == 0) {
        numLidos = LER_LerParametros("ii", &inxLista, &CondRetEsp);

        if((numLidos != 2) || (! ValidarInxTabuleiro(inxLista, NAO_VAZIO)))
            return TST_CondRetParm;

        tipo = PEC_obterTipo(vtTabuleiros[inxLista]);
        return TST_CompararInt(CondRetEsp, tipo, "Tipo errada ao obter tipo.");
    }
    else if(strcmp(ComandoTeste, SETAR_TIPO_CMD) == 0) {
        numLidos = LER_LerParametros("ii", &inxLista, &tipo);

        if((numLidos != 2) || (! ValidarInxTabuleiro(inxLista, NAO_VAZIO)))
            return TST_CondRetParm;

        PEC_setarTipo(vtTabuleiros[inxLista], tipo);
        return TST_CondRetOK;
    }
    else if(strcmp(ComandoTeste, OBTER_CARACTER_CMD) == 0) {
        numLidos = LER_LerParametros("is", &inxLista, StringDado);

        if((numLidos != 2) || (! ValidarInxTabuleiro(inxLista, NAO_VAZIO)))
            return TST_CondRetParm;

        caracter = PEC_obterCaracter(vtTabuleiros[inxLista]);
        return TST_CompararEspaco(StringDado, &caracter, 1, "Caracter errado ao obter caracter.");
    }
    else if(strcmp(ComandoTeste, SETAR_CARACTER_CMD) == 0) {
        numLidos = LER_LerParametros("is", &inxLista, StringDado);

        if((numLidos != 2) || (! ValidarInxTabuleiro(inxLista, NAO_VAZIO)))
            return TST_CondRetParm;

        PEC_setarCaracter(vtTabuleiros[inxLista], StringDado[0]);
        return TST_CondRetOK;
    }

    return TST_CondRetNaoConhec;
} /* Fim fun��o: TPEC &Testar peca */

/*****  Código das funções encapsuladas no módulo  *****/

/***********************************************************************
*
*  $FC Fun��o: TPEC -Validar indice de peca
*
***********************************************************************/

int ValidarInxTabuleiro(int inxLista, int Modo)
{
    if((inxLista <  0) || (inxLista >= DIM_VT_PECA))
        return FALSE;

    if(Modo == VAZIO) {
        if(vtTabuleiros[inxLista] != 0)
            return FALSE;
    } else {
        if(vtTabuleiros[inxLista] == 0)
            return FALSE;
    }
    return TRUE;
} /* Fim fun��o: TPEC -Validar indice de lista */


/********** Fim do m�dulo de implementa��o: Testpeca  Teste do modulo peca **********/
