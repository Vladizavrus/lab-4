cmake_minimum_required(VERSION 3.27)
project(template_tree)

set(CMAKE_CXX_STANDARD 23)

add_executable(template_tree main.cpp
        heap.h
        BST.h
        assert.h
        menu.h
        testing_structs.h)
