cmake_minimum_required(VERSION 3.24)
project(hw8 C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(hw7
        BinaryTree.c
        BinaryTree.h
        BinaryTree_main.c
        Makefile)
