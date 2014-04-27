#!/bin/sh
SCRIPT=$(realpath -s $0)
BASEDIR=$(dirname $SCRIPT)

cd $BASEDIR/../Scripts

# Run list
$BASEDIR/../build/test_lista /stestelista /l../Produto/testelista /a../Produto/estatisticas
$BASEDIR/../build/test_lista /stestelistaint /l../Produto/testelistaint /a../Produto/estatisticas

# Run peca
$BASEDIR/../build/test_peca /stestepeca /l../Produto/testepeca /a../Produto/estatisticas

# Run tabuleiro
$BASEDIR/../build/test_tabuleiro /stestetabuleiro /l../Produto/testetabuleiro /a../Produto/estatisticas
