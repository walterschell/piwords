cmake_minimum_required(VERSION 2.8.12)
project(piwords)

set (CMAKE_CXX_STANDARD 11)
set (CMAKE_C_STANDARD 11)

find_path(MPFR_PATH mpfr.h)

if(MPFR_PATH MATCHES NOTFOUND)
    message(FATAL_ERROR "mpfr required")
endif()

add_subdirectory(triesearch)

set(piwords_SRCS
    src/piwords.cpp
    src/piqpr8.c
    src/gen_val.c
    # src/pihex.c
    )

add_executable(piwords ${piwords_SRCS})
target_link_libraries(piwords trie mpfr)
