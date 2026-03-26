//
// Created by yaxkin on 3/24/26.
//

#ifndef ARBOLES_LISTA_H
#define ARBOLES_LISTA_H
#include "../tads/NodoLista.h"
#include "../clases/Product.h"

class Lista
{
    using Nodo = NodoLista;
private:
    Nodo* cabeza;
public:
    Lista(Nodo* cabeza);
    ~Lista();

    Nodo* getCabeza();
    void setCabeza(Nodo* cab);
    void agregarSiguiente(Nodo* sig);
};


#endif //ARBOLES_LISTA_H