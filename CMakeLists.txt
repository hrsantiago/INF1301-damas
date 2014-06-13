cmake_minimum_required(VERSION 2.8)
project(damas)

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR}/cmake ${CMAKE_MODULE_PATH})

# default build type
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()
message(STATUS "Build type: " ${CMAKE_BUILD_TYPE})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c99 -pipe -Wall")
set(CMAKE_CXX_FLAGS_DEBUG "-O0 -g -D_DEBUG")
set(CMAKE_CXX_FLAGS_RELEASE "-Wno-error -O4 -ffast-math")

set(SOURCES
  Fontes/main.c
  Fontes/lista.c
  Fontes/lista.h
  Fontes/tabuleiro.c
  Fontes/tabuleiro.h
  Fontes/peca.c
  Fontes/peca.h
  Fontes/jogo.c
  Fontes/jogo.h
  Fontes/tipos.h
)

add_executable(${PROJECT_NAME} ${SOURCES})

#build tests
include(testelista)
include(testetabuleiro)
include(testepeca)
