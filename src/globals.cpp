//
// Created by yaxkin on 3/24/26.
//
#include "globals.h"

int contadorNodo = 0;
int contadorCells = 0;
int contadorProductos = 0;
int gradoArbolB = 3;
ArbolB* arbolB = new ArbolB(gradoArbolB);
ArbolAVL* arbolAVL = new ArbolAVL(nullptr);
Lista* listaDesordenada = new Lista(nullptr);
Lista* listaOrdenada = new Lista(nullptr);
logger* loggerGlob = new logger();

void limpiarDatos()
{
    delete arbolB;
    delete arbolAVL;
    delete listaDesordenada;
    delete listaOrdenada;

    arbolB = new ArbolB(gradoArbolB);
    arbolAVL = new ArbolAVL(nullptr);
    listaDesordenada = new Lista(nullptr);
    listaOrdenada = new Lista(nullptr);

    std::cout << "Estructuras limpiadas" << std::endl;
}

