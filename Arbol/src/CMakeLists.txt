set(HEADER_LIST "${arbol_SOURCE_DIR}/include/*.hpp")
add_executable(arbol main.cpp BST.cpp ExperimentoInsertar.cpp ExperimentoContiene.cpp)
target_include_directories(arbol PUBLIC ../include)