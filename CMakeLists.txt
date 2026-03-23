cmake_minimum_required(VERSION 3.10)

project(Arboles)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Agregar los archivos fuente
set(SOURCES
        src/main.cpp
        src/parsing/csvReader.cpp
)

add_executable(Arboles ${SOURCES})

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