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
    void balancear(Nodo* rz);

    void listarInorder(Nodo* rz);
};


#endif //ARBOLES_AVL_H
