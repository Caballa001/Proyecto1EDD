//
// Created by yaxkin on 3/24/26.
//

#ifndef ARBOLES_NODO_H
#define ARBOLES_NODO_H
#include "clases/Product.h"

class NodoLista
{
private:
    Product* valor;
    NodoLista* siguiente;
public:
    NodoLista(Product* valor);
    ~NodoLista();

    Product* getValor();
    NodoLista* getSigiente();
    void setSigiente(NodoLista* sig);
};

#endif //ARBOLES_NODO_H

