//
// Created by yaxkin on 3/24/26.
//

#include "../tads/NodoLista.h"

NodoLista::NodoLista(Product* valor)
{
    this->valor = valor;
    this->siguiente = nullptr;
}

NodoLista::~NodoLista()
{
    delete this->valor;
    this->siguiente = nullptr;
}

Product* NodoLista::getValor()
{
    return this->valor;
}

NodoLista* NodoLista::getSigiente()
{
    return this->siguiente;
}

void NodoLista::setSigiente(NodoLista* sig)
{
    this->siguiente = sig;
}
