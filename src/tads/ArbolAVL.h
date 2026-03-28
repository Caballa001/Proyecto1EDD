//
// Created by yaxkin on 3/24/26.
//

#ifndef ARBOLES_AVL_H
#define ARBOLES_AVL_H
#include "../tads/NodoAVL.h"
#include "../clases/Product.h"
#include "../helperMethods/valorOrdenarAZ.h"
#include <iostream>
#include <string>
#include <vector>

class ArbolAVL
{
    using Nodo = NodoAVL;
private:
    Nodo* raiz;

public:
    ArbolAVL(Nodo* rz);
    ~ArbolAVL();

    Nodo* getRaiz();
    void setRaiz(Nodo* rz);

    void agregarNodo(Nodo* nodo, Nodo* rz);
    void eliminarNodo(const std::string& nombre);
    Nodo* checkBalance(Nodo* rz);
    Nodo* leftLeft(Nodo* nodo);
    Nodo* rightRight(Nodo* nodo);
    Nodo* leftRight(Nodo* nodo);
    Nodo* rightLeft(Nodo* nodo);
    int obtenerAltura(Nodo* nodo);
    int actualizarFB(Nodo* nodo);

    Product* buscarProductPorNombre(Nodo* rz, std::string nombre);
    std::string encontrarNombrePorBarcode(Nodo* rz, const std::string& barcode);
    Nodo* encontrarMinimo(Nodo* rz);
    Nodo* eliminarPorNombre(Nodo* rz, const std::string& nombre);

    void listarInorder(Nodo* rz);
};


#endif //ARBOLES_AVL_H
