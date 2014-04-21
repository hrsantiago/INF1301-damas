cmake_minimum_required(VERSION 2.8)
project(test_tabuleiro)

set(SOURCES
    testtabuleiro.c

    ../../src/lista.c
    ../../src/lista.h
    ../../src/peca.c
    ../../src/peca.h
    ../../src/tabuleiro.c
    ../../src/tabuleiro.h
)

add_executable(${PROJECT_NAME} ${SOURCES})

FIND_LIBRARY(AUTOTEST_LIBRARY NAMES libautotest.so)
target_link_libraries(${PROJECT_NAME} ${AUTOTEST_LIBRARY})
