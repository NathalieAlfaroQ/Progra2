# CMake principal para el proyecto Calculadora
# NO DEBEN MODIFICAR ESTE ARCHIVO

cmake_minimum_required(VERSION 3.15)

project(Calculadora)

# Use C++11
set(CMAKE_CXX_STANDARD 17)
# Require (at least) it
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake/modules/)

add_subdirectory(src)
add_subdirectory(tests)