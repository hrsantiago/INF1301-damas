#ifndef TIPOS_H
#define TIPOS_H

/************************************************************
*  declara os identificadores de tipos dos espaços de dados
*  a serem utilizados por um determinado construto.
**************************************************************/

typedef enum {
    CED_ID_TIPO_VALOR_NULO,
    JOG_Jogo,
    TAB_Tabuleiro, /* estrutura com cabeca de lista de listas=tabuleiro */
    PEC_Peca,
    CED_ID_TIPO_ILEGAL = 999
} CED_tpIdTipoEspaco ;

#endif
