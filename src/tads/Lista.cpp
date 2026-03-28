//
// Created by yaxkin on 3/24/26.
//

#include "../tads/Lista.h"

#include <iostream>

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

void Lista::agregar(Nodo* primero) //Agrega por delante
{
    if (this->cabeza == nullptr)
    {
        this->cabeza = primero;
        return;
    }
    if (isUnico(this->cabeza, primero->getValor()->barcode) == false)
    {
        std::cout << "Producto con barcode " << primero->getValor()->barcode << " ya existe en la lista, se descarta el producto" << std::endl;
        delete primero;
        return;
    }
    Nodo* nodoDesplazado = this->cabeza;
    this->cabeza = primero;
    this->cabeza->setSigiente(nodoDesplazado);
}

bool Lista::isUnico(Nodo* cbz, std::string barcode)
{
    if (cbz == nullptr) return true;
    if (cbz->getValor()->barcode == barcode) return false;
    return isUnico(cbz->getSigiente(), barcode);
}

Product* Lista::buscarPorNombre(std::string nombre)
{
    Nodo* aux = this->cabeza;
    while (aux != nullptr)
    {
        if (aux->getValor()->name == nombre)
        {
            return aux->getValor();
        }

        aux = aux->getSigiente();
    }
    return nullptr;
}

void Lista::agregarEnOrden(Nodo* nodo)
{
    if (this->cabeza == nullptr)
    {
        this->cabeza = nodo;
        return;
    }
    if (isUnico(this->cabeza, nodo->getValor()->barcode) == false)
    {
        std::cout << "Producto con barcode " << nodo->getValor()->barcode << " ya existe en la lista, se descarta el producto" << std::endl;
        delete nodo;
        return;
    }
    if (this->cabeza->getValor()->name > nodo->getValor()->name)
    {
        nodo->setSigiente(this->cabeza);
        this->cabeza = nodo;
        return;
    }

    Nodo* aux = this->cabeza;
    while (aux->getSigiente() != nullptr)
    {
        if (aux->getSigiente()->getValor()->name > nodo->getValor()->name)
        {
            Nodo* nodoDesplazado = aux->getSigiente();
            aux->setSigiente(nodo);
            nodo->setSigiente(nodoDesplazado);
            return;
        }
        aux = aux->getSigiente();
    }
    aux->setSigiente(nodo);
}

void Lista::eliminarPorNombre(std::string nombre)
{
    if (this->cabeza == nullptr) return;

    if (this->cabeza->getValor()->name == nombre)
    {
        Nodo* aEliminar = this->cabeza;
        this->cabeza = this->cabeza->getSigiente();
        delete aEliminar;
        return;
    }

    Nodo* aux = this->cabeza;
    while (aux->getSigiente() != nullptr)
    {
        if (aux->getSigiente()->getValor()->name == nombre)
        {
            Nodo* aEliminar = aux->getSigiente();
            aux->setSigiente(aEliminar->getSigiente());
            delete aEliminar;
            return;
        }
        aux = aux->getSigiente();
    }
}

void Lista::listarProductos()
{
    if (this->cabeza == nullptr)
    {
        std::cout << "No hay Productos que mostrar" << std::endl;
        return;
    }
    Nodo* cab = this->cabeza;
    while (cab != nullptr)
    {
        Product* p = cab->getValor();
        std::cout << p->name << std::endl;
        cab = cab->getSigiente();
    }
}