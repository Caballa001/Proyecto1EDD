//
// Created by yaxkin on 3/25/26.
//

#ifndef ARBOLES_GENERARDOT_H
#define ARBOLES_GENERARDOT_H
#include "../tads/NodoAVL.h"

void generarDot(NodoAVL* nodo);

void contenidoDigraph(NodoAVL* nodo, std::string& content);

void checkDirectoryExists(const std::string& path);


#endif //ARBOLES_GENERARDOT_H