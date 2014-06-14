#ifndef TIPOS_H
#define TIPOS_H

/************************************************************
*  $MCD Módulo de declaração: TIP Tipos 
*
*  Arquivo gerado:              TIPOS.h
*  Letras identificadoras:      TIP
*  
*  Projeto: damas
*  Arquivo: damas\fontes\tipos.h
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
