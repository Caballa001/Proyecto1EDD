cmake_minimum_required(VERSION 3.10)

project(Arboles)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Agregar los archivos fuente
set(SOURCES
        src/main.cpp
        src/parsing/csvReader.cpp
        src/clases/Product.cpp
        src/clases/Product.h
        src/tads/Lista.cpp
        src/tads/Lista.h
        src/tads/NodoLista.cpp
        src/tads/NodoLista.h
        src/tads/ArbolAVL.cpp
        src/tads/ArbolAVL.h
        src/tads/NodoAVL.cpp
        src/tads/NodoAVL.h
        src/parsing/loader.cpp
        src/helperMethods/valorOrdenAZ.cpp
        src/globals.cpp
        src/globals.h
        src/helperMethods/valorOrdenarAZ.h
        src/parsing/csvReader.h
        src/parsing/loader.h
        src/export/generarDot.cpp
        src/export/generarDot.h
)

# Graphviz
find_package(PkgConfig REQUIRED)
pkg_check_modules(GRAPHVIZ REQUIRED libgvc libcgraph)

add_executable(Arboles ${SOURCES})
target_include_directories(Arboles PRIVATE ${GRAPHVIZ_INCLUDE_DIRS})
target_link_libraries(Arboles PRIVATE ${GRAPHVIZ_LIBRARIES})

# Directorios a incluir
target_include_directories(Arboles PRIVATE
        "${CMAKE_SOURCE_DIR}/src"
)

if(MSVC)
    target_compile_options(Arboles PRIVATE /W4 /WX)
else()
    target_compile_options(Arboles PRIVATE -Wall -Wextra -Wpedantic)
endif()

# Coloca el binary en /bin/
set_target_properties(Arboles PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)