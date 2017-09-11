cmake_minimum_required(VERSION 2.8.12)
project(piwords)
add_subdirectory(triesearch)

set(piwords_SRCS
src/piwords.cpp)

add_executable(piwords ${piwords_SRCS})
target_link_libraries(piwords trie)