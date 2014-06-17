cmake_minimum_required(VERSION 2.8)
project(damas)

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR}/cmake ${CMAKE_MODULE_PATH})

# default build type
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()
message(STATUS "Build type: " ${CMAKE_BUILD_TYPE})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D_DEBUG -std=c99 -pipe -Wall")
set(CMAKE_CXX_FLAGS_DEBUG "-O0 -g")
set(CMAKE_CXX_FLAGS_RELEASE "-Wno-error -O4 -ffast-math")

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_definitions("-D_DEBUG")
endif()

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

FIND_LIBRARY(AUTOTEST_LIBRARY NAMES libautotest.so)
FIND_PATH(AUTOTEST_INCLUDE_DIR NAMES autotest/generico.h)

target_link_libraries(${PROJECT_NAME} ${AUTOTEST_LIBRARY})
include_directories(${AUTOTEST_INCLUDE_DIR}/autotest)

#build tests
include(testelista)
include(testetabuleiro)
include(testepeca)
