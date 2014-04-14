#!/bin/sh
SCRIPT=$(realpath -s $0)
BASEDIR=$(dirname $SCRIPT)

# Run list
cd $BASEDIR/lista
$BASEDIR/../build/tests/lista/test_lista /stestelista /ltestelista /aestatisticas

# Run peca
cd $BASEDIR/peca
$BASEDIR/../build/tests/peca/test_peca /stestepeca /ltestepeca /aestatisticas

# Run tabuleiro
cd $BASEDIR/tabuleiro
$BASEDIR/../build/tests/tabuleiro/test_tabuleiro /stestetabuleiro /ltestetabuleiro /aestatisticas
