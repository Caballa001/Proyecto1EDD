//
// Created by yaxkin on 3/24/26.
//

#include "../tads/Lista.h"

Lista::Lista(NodoLista* cabeza)
{
    this->cabeza = cabeza;
}

Lista::~Lista()
{
    NodoLista* aux = this->cabeza;
    while (aux != nullptr)
    {
        NodoLista* siguiente = aux->getSigiente();
        delete aux;
        aux = siguiente;
    }
}

NodoLista* Lista::getCabeza()
{
    return this->cabeza;
}

void Lista::setCabeza(NodoLista* cab)
{
    this->cabeza = cab;
}

void Lista::agregarSiguiente(NodoLista* sig)
{
    if (this->cabeza == nullptr)
    {
        this->cabeza = sig;
        return;
    }
    NodoLista* aux = this->cabeza;
    while (aux->getSigiente() != nullptr)
    {
        aux = aux->getSigiente();
    }
    aux->setSigiente(sig);
}
