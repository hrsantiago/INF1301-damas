/*
 * Henrique Santiago
 * Marcelo Resende
 * Rafael Haeusler
*/

#include    <string.h>
#include    <stdio.h>
#include    <malloc.h>

#include    "TST_Espc.h"
#include    "generico.h"
#include    "lerparm.h"

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

Peca *vtPecas[DIM_VT_PECA];

/***** Protótipos das funções encapuladas no módulo *****/

static int ValidarInxPeca(int inxLista, int Modo);

/*****  Código das funções exportadas pelo módulo  *****/


/***********************************************************************
*
*  $FC Função: TLIS &Testar peca
*
*  $ED Descrição da função
*     Podem ser criadas até 10 pecas, identificadas pelos índices 0 a 9
*
*     Comandos disponíveis:
*
*     =resetteste
*           - anula o vetor de pecas. Provoca vazamento de memória
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
            vtPecas[i] = NULL;

        return TST_CondRetOK;
    }
    else if(strcmp(ComandoTeste, CRIAR_PECA_CMD) == 0) {
        numLidos = LER_LerParametros("iis", &inxLista, &tipo, StringDado);

        if((numLidos != 3) || (! ValidarInxPeca(inxLista, VAZIO)))
            return TST_CondRetParm;

        vtPecas[inxLista] = PEC_criar(tipo, StringDado[0]);
        return TST_CompararPonteiroNulo(1, vtPecas[inxLista], "Erro em ponteiro de nova peca.");
    }
    else if(strcmp(ComandoTeste, DESTRUIR_PECA_CMD) == 0) {
        numLidos = LER_LerParametros("i", &inxLista);

        if((numLidos != 1) || (! ValidarInxPeca(inxLista, NAO_VAZIO)))
            return TST_CondRetParm;

        PEC_destruir(vtPecas[inxLista]);
        vtPecas[inxLista] = NULL;

        return TST_CondRetOK;
    }
    else if(strcmp(ComandoTeste, OBTER_TIPO_CMD) == 0) {
        numLidos = LER_LerParametros("ii", &inxLista, &CondRetEsp);

        if((numLidos != 2) || (! ValidarInxPeca(inxLista, NAO_VAZIO)))
            return TST_CondRetParm;

        tipo = PEC_obterTipo(vtPecas[inxLista]);
        return TST_CompararInt(CondRetEsp, tipo, "Tipo errada ao obter tipo.");
    }
    else if(strcmp(ComandoTeste, SETAR_TIPO_CMD) == 0) {
        numLidos = LER_LerParametros("ii", &inxLista, &tipo);

        if((numLidos != 2) || (! ValidarInxPeca(inxLista, NAO_VAZIO)))
            return TST_CondRetParm;

        PEC_setarTipo(vtPecas[inxLista], tipo);
        return TST_CondRetOK;
    }
    else if(strcmp(ComandoTeste, OBTER_CARACTER_CMD) == 0) {
        numLidos = LER_LerParametros("is", &inxLista, StringDado);

        if((numLidos != 2) || (! ValidarInxPeca(inxLista, NAO_VAZIO)))
            return TST_CondRetParm;

        caracter = PEC_obterCaracter(vtPecas[inxLista]);
        return TST_CompararEspaco(StringDado, &caracter, 1, "Caracter errado ao obter caracter.");
    }
    else if(strcmp(ComandoTeste, SETAR_CARACTER_CMD) == 0) {
        numLidos = LER_LerParametros("is", &inxLista, StringDado);

        if((numLidos != 2) || (! ValidarInxPeca(inxLista, NAO_VAZIO)))
            return TST_CondRetParm;

        PEC_setarCaracter(vtPecas[inxLista], StringDado[0]);
        return TST_CondRetOK;
    }

    return TST_CondRetNaoConhec;
}


/*****  Código das funções encapsuladas no módulo  *****/

/***********************************************************************
*
*  $FC Função: TLIS -Validar indice de peca
*
***********************************************************************/

int ValidarInxPeca(int inxLista, int Modo)
{
    if((inxLista <  0) || (inxLista >= DIM_VT_PECA))
        return FALSE;

    if(Modo == VAZIO) {
        if(vtPecas[inxLista] != 0)
            return FALSE;
    } else {
        if(vtPecas[inxLista] == 0)
            return FALSE;
    }
    return TRUE;
}

