#!/bin/bash

echo "Compilando el proyecto..."
cmake -DCMAKE_CXX_COMPILER=g++-14 .
make
echo "Proyecto construido exitosamente."
echo "Ejecutando el programa..."
./bin/Arboles "$@"

