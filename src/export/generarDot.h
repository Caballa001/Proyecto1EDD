//
// Created by yaxkin on 3/25/26.
//

#ifndef ARBOLES_GENERARDOT_H
#define ARBOLES_GENERARDOT_H
#include "../tads/NodoAVL.h"
#include "../tads/NodoB.h"

void generarDotAVL(NodoAVL* nodo);

void contenidoAVL(NodoAVL* nodo, std::string& content);

void checkDirectoryExists(const std::string& path);

void generarDotBtree(NodoB* nodo);

void generarDotBtree(NodoB* nodo);

void nodosBtree(NodoB* nodo, std::string& content);

void conexionesBtree(NodoB* nodo, std::string& content);

void conexionesBtree(NodoB* nodo, std::string& content);


#endif //ARBOLES_GENERARDOT_H
