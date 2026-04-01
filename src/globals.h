//
// Created by yaxkin on 3/24/26.
//

#ifndef ARBOLES_GLOBALS_H
#define ARBOLES_GLOBALS_H

#include "tads/ArbolB.h"
#include "./tads/ArbolAVL.h"
#include "./tads/Lista.h"
#include "./logger/logger.h"

extern int contadorNodo;
extern int contadorCells;
extern int contadorProductos;
extern ArbolB* arbolB;
extern ArbolAVL* arbolAVL;
extern Lista* listaDesordenada;
extern Lista* listaOrdenada;
extern logger* loggerGlob;
extern int gradoArbolB;
//TODO add other structures

void limpiarDatos();


#endif //ARBOLES_GLOBALS_H