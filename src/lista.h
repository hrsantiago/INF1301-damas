#ifndef LISTA_
#define LISTA_
/*
 * Henrique Santiago
 * Marcelo Resender
 * Rafael Haeusler
*/

/***************************************************************************
*
*  $MCD Módulo de definição: LIS  Lista duplamente encadeada
*
*  Arquivo gerado:              LISTA.h
*  Letras identificadoras:      LIS
*
*  Nome da base de software:    Arcabouço para a automação de testes de programas redigidos em C
*  Arquivo da base de software: D:\AUTOTEST\PROJETOS\LISTA.BSW
*
*  Projeto: INF 1301 / 1628 Automatização dos testes de módulos C
*  Gestor:  LES/DI/PUC-Rio
*  Autores: avs
*
*  $HA Histórico de evolução:
*     Versão  Autor    Data     Observações
*     4       avs   01/fev/2006 criar linguagem script simbólica
*     3       avs   08/dez/2004 uniformização dos exemplos
*     2       avs   07/jul/2003 unificação de todos os módulos em um só projeto
*     1       avs   16/abr/2003 início desenvolvimento
*
*  $ED Descrição do módulo
*     Implementa listas genéricas duplamente encadeadas.
*     Podem existir n listas em operação simultaneamente.
*     As listas possuem uma cabeça encapsulando o seu estado.
*
*     Cada lista é homogênea quanto ao tipo dos dados que armazena.
*     Cada elemento da lista referencia o valor que contém.
*
*     Os ponteiros para os dados são copiados para elementos da lista.
*        Não é copiado o valor apontado por estes ponteiros.
*
*     O controle da destruição do valor de um elemento a ser excluído
*        é realizado por uma função fornecida pelo usuário.
*
*     Cada lista referencia uma função que determina como devem ser
*        desalocados os dados nela contidos.
*
*     A função de liberação dos valores contidos nos elementos deve
*        assegurar a liberação de todos os espaços referênciados pelo
*        valor contido em um elemento.
*        Esta função é chamada antes de se desalocar um elemento
*        de uma lista.
*        Caso não seja necessário desalocar o valor referenciado pelo
*        elemento, o ponteiro para a função de liberação poderá ser NULL .
*        Caso o elemento da lista seja a única âncora do valor referenciado,
*        esta função deve promover a destruição (free) desse valor e
*        de todos os dados nele ancorados.
*
***************************************************************************/
 
#ifdef LISTA_OWN
   #define LISTA_EXT
#else
   #define LISTA_EXT extern
#endif

typedef struct LIS_tagLista *LIS_tppLista ;

typedef enum {
    LIS_CondRetOK,
    LIS_CondRetListaVazia,
    LIS_CondRetFimLista,
    LIS_CondRetNaoAchou,
    LIS_CondRetFaltouMemoria
} LIS_tpCondRet;

LIS_tppLista LIS_CriarLista(void(*ExcluirValor)(void *pDado));
void LIS_DestruirLista(LIS_tppLista pLista);
void LIS_EsvaziarLista(LIS_tppLista pLista);
LIS_tpCondRet LIS_InserirElementoAntes(LIS_tppLista pLista, void *pValor);
LIS_tpCondRet LIS_InserirElementoApos(LIS_tppLista pLista, void *pValor);
LIS_tpCondRet LIS_ExcluirElemento(LIS_tppLista pLista);
void *LIS_ObterValor(LIS_tppLista pLista);
void IrInicioLista(LIS_tppLista pLista);
void IrFinalLista(LIS_tppLista pLista);
LIS_tpCondRet LIS_AvancarElementoCorrente(LIS_tppLista pLista, int numElem);
LIS_tpCondRet LIS_ProcurarValor(LIS_tppLista pLista, void *pValor);

#undef LISTA_EXT

#endif
