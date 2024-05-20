
# Agreguen acá todos los archivos .cc que necesiten para compilar su tarea.
set(TESTFILES
# Si agregan más archivos de pruebas en test/ entonces deben agregarlos acá
  bst_test.cc
  calculadora_test.cc
  fibonacci_test.cc
  shunting_yard_test.cc
  token_test.cc
  tokenizer_test.cc
  postfijo_test.cc
  

# Pruebas de ejemplo (también en test/):
    bst_test.cc
    fibonacci_test.cc

# Si agregan más archivos .cc en src/ entonces deben agregarlos acá. De lo contrario,
# no serán compilados y no podrán ser usados en las pruebas.
    ${Calculadora_SOURCE_DIR}/src/calculadora.cc
    ${Calculadora_SOURCE_DIR}/src/postfijo.cc
    ${Calculadora_SOURCE_DIR}/src/shunting_yard.cc
    ${Calculadora_SOURCE_DIR}/src/token.cc
    ${Calculadora_SOURCE_DIR}/src/tokenizer.cc
)

# Usualmente NO DEBEN MODIFICAR NADA DE AQUÍ EN ADELANTE.
# Usualmente NO DEBEN MODIFICAR NADA DE AQUÍ EN ADELANTE.
# Usualmente NO DEBEN MODIFICAR NADA DE AQUÍ EN ADELANTE.
# Usualmente NO DEBEN MODIFICAR NADA DE AQUÍ EN ADELANTE.
# Usualmente NO DEBEN MODIFICAR NADA DE AQUÍ EN ADELANTE.
# Usualmente NO DEBEN MODIFICAR NADA DE AQUÍ EN ADELANTE.

# Quickstart CMake taken from:
# https://google.github.io/googletest/quickstart-cmake.html

set(CMAKE_CXX_STANDARD 17)

include(FetchContent)
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG release-1.12.1
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

OPTION(COVERAGE "Enable coverage reporting" OFF)

FetchContent_MakeAvailable(googletest)
enable_testing()



set(TEST_MAIN unit_tests)   # Default name for test executable (change if you wish).
set(TEST_RUNNER_PARAMS "")  # Any arguemnts to feed the test runner (change as needed).

# Se define un ejecutable de pruebas "calculadora_test",
# que requiere los siguientes archivos .cc para ser compilado.
add_executable(${TEST_MAIN} ${TESTFILES})

# calculadora_test requiere los archivos de encabezados
# en el folder include

target_include_directories(${TEST_MAIN}
    PUBLIC "${Calculadora_SOURCE_DIR}/include")

# Finalmente, enlazamos con la librería de Google Test
target_link_libraries(
    ${TEST_MAIN} PRIVATE ${LIBRARY_NAME}
    GTest::gtest_main
)
set_target_properties(${TEST_MAIN} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR})

include(GoogleTest)

# Añadan esto para permitir que ctest pueda descubrir
# las pruebas automáticamente
gtest_discover_tests(${TEST_MAIN})

add_test(
    # Use some per-module/project prefix so that it is easier to run only tests for this module
    NAME ${LIBRARY_NAME}.${TEST_MAIN}
    COMMAND ${TEST_MAIN} ${TEST_RUNNER_PARAMS})

if (COVERAGE MATCHES "ON")
    include(CodeCoverage)
    append_coverage_compiler_flags_to_target(${TEST_MAIN})
    # If unwanted files are included in the coverage reports, you can 
    # adjust the exclude patterns on line 83. 
    setup_target_for_coverage_lcov(
                            NAME coverage            # Name for custom target.
                            EXECUTABLE ${TEST_MAIN}        # Name of the test driver executable that runs the tests.
                                                # NOTE! This should always have a ZERO as exit code
                                                # otherwise the coverage generation will not complete.
                            coverage_out        # Name of output directory.
                            )
else() 
    add_custom_target(coverage 
        COMMAND echo "${Red}Code coverage only available in coverage builds." 
        COMMAND echo "${Green}Make a new build directory and rerun cmake with -DCMAKE_BUILD_TYPE=Coverage to enable this target.${ColorReset}" 
    )
endif()