cmake_minimum_required(VERSION 2.8.12)
project(piwords)

set (CMAKE_CXX_STANDARD 11)

add_subdirectory(triesearch)

set(piwords_SRCS
    src/piwords.cpp
    src/piqpr8.c
    src/gen_val.c
    )

add_executable(piwords ${piwords_SRCS})
target_link_libraries(piwords trie)
