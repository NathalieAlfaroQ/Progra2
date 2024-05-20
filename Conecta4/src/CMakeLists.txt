set(HEADER_LIST "${CuatroEnLinea_SOURCE_DIR}/include/*.hpp")
    add_executable(CuatroEnLinea main.cpp tablero.cpp jugadores.cpp)
        target_include_directories(CuatroEnLinea PUBLIC ../include)
