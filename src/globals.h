//
// Created by yaxkin on 3/24/26.
//

#ifndef ARBOLES_GLOBALS_H
#define ARBOLES_GLOBALS_H

#include "./tads/ArbolAVL.h"
#include "./tads/Lista.h"
#include "./tads/NodoAVL.h"
#include "./tads/NodoLista.h"
#include "./clases/Product.h"
#include "./logger/logger.h"

extern ArbolAVL* arbolAVL;
extern Lista* listaDesordenada;
extern Lista* listaOrdenada;
extern logger* loggerGlob;
//TODO add other structures

void limpiarDatos();


#endif //ARBOLES_GLOBALS_H