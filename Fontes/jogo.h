/*
 * Henrique Santiago
 * Marcelo Resende
 * Rafael Haeusler
*/

#ifndef JOGO_H
#define JOGO_H

typedef enum _JOG_tpCondRet{
    JOG_CondRetOK, /* Concluiu corretamente */
    JOG_CondRetOpcaoInvalida, /* Opcao invalida no menu */
    JOG_CondRetJogoInexistente, /* o jogo não existe */
} JOG_tpCondRet;

typedef struct _Jogo Jogo;

Jogo *JOG_criar();
JOG_tpCondRet JOG_destruir(Jogo *jogo);
void JOG_rodar(Jogo *jogo);

#endif
