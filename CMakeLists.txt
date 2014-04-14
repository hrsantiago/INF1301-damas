cmake_minimum_required(VERSION 2.8)
project(damas)

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR}/cmake ${CMAKE_MODULE_PATH})

# default build type
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()
message(STATUS "Build type: " ${CMAKE_BUILD_TYPE})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c99 -pipe ${WARNS_FLAGS}")
set(CMAKE_CXX_FLAGS_DEBUG "-O0 -g -D_DEBUG")
set(CMAKE_CXX_FLAGS_RELEASE "-Wno-error -O4 -ffast-math")

set(SOURCES
  src/main.c
  src/lista.c
  src/lista.h
  src/tabuleiro.c
  src/tabuleiro.h
  src/peca.c
  src/peca.h
)

add_executable(${PROJECT_NAME} ${SOURCES})

#build tests
add_subdirectory(tests)
