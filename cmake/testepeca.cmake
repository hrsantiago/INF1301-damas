cmake_minimum_required(VERSION 2.8)
project(test_peca)

set(SOURCES
    ../Fontes/testpeca.c
    ../Fontes/peca.c
    ../Fontes/peca.h
)

add_executable(${PROJECT_NAME} ${SOURCES})

FIND_LIBRARY(AUTOTEST_LIBRARY NAMES libautotest.so)
FIND_PATH(AUTOTEST_INCLUDE_DIR NAMES autotest/generico.h)

target_link_libraries(${PROJECT_NAME} ${AUTOTEST_LIBRARY})
include_directories(${AUTOTEST_INCLUDE_DIR}/autotest)
