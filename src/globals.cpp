//
// Created by yaxkin on 3/24/26.
//
#include "globals.h"

ArbolAVL* arbolAVL = new ArbolAVL(nullptr);
Lista* listaDesordenada = new Lista(nullptr);
Lista* listaOrdenada = new Lista(nullptr);
logger* loggerGlob = new logger();

void limpiarDatos()
{
    delete arbolAVL;
    delete listaDesordenada;
    delete listaOrdenada;

    arbolAVL = new ArbolAVL(nullptr);
    listaDesordenada = new Lista(nullptr);
    listaOrdenada = new Lista(nullptr);

    std::cout << "Estructuras limpiadas" << std::endl;
}

