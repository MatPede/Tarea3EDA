cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_COMPILER "/usr/bin/g++")
# set the project name

project(Calculadora
VERSION 1.0
LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

#add_subdirectory(src)
#add_subdirectory(calculadoras)

add_executable(calculadora calculadora/calculadora.cpp src/treeNode.cpp src/treeListNode.cpp src/treeList.cpp src/tree.cpp)
target_include_directories(calculadora PUBLIC ${PROJECT_SOURCE_DIR}/include)


# add the executable