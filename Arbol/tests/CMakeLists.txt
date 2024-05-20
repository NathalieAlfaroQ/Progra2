# Quickstart CMake taken from:
# https://google.github.io/googletest/quickstart-cmake.html
# GoogleTest requires at least C++14
set(CMAKE_CXX_STANDARD 14)
include(FetchContent)
FetchContent_Declare(
googletest
URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)
enable_testing()
# Se define un ejecutable de pruebas "cuatroenlinea_test",
# que requiere los siguientes archivos .cc para ser compilado.
add_executable(arbol_test
BST_test.cc
${arbol_SOURCE_DIR}/src/BST.cpp
)
# Además, se añaden los archivos de encabezados
target_include_directories(arbol_test
PUBLIC
"${arbol_SOURCE_DIR}/include"
)
# Finalmente, enlazamos con la biblioteca de Google Test
target_link_libraries(arbol_test
GTest::gtest_main
)
include(GoogleTest)
# Añadan esto para permitir que ctest pueda descubrir las pruebas automáticamente
gtest_discover_tests(arbol_test)
