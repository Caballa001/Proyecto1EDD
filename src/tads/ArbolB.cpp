//
// Created by yaxkin on 3/29/26.
//

#include "ArbolB.h"
#include "tads/NodoB.h"
#include "helperMethods/helperMethods.h"

ArbolB::ArbolB(int grad)
{
    this->raiz = nullptr;
    this->grado = grad;
}

ArbolB::~ArbolB()
{
    delete this->raiz;
}

void ArbolB::recorrer()
{
    if (this->raiz == nullptr)
    {
        return;
    }
    this->raiz->recorrer();
}

ArbolB::Nodo* ArbolB::getRaiz()
{
    return this->raiz;
}

Product* ArbolB::buscar(std::string fechaExp)
{
    if (this->raiz == nullptr)
    {
        return nullptr;
    }
    return this->raiz->buscar(fechaExp);
}

void ArbolB::insertar(Product* producto)
{
    if (this->raiz == nullptr)
    {
        raiz = new NodoB(grado, true);
        raiz->setClaveInPos(0, producto);
        raiz->setNumClaves(1);
    }
    else
    {
        if (raiz->getNumClaves() == 2*grado -1) // Raiz esta llena, divide y asciende medio como nueva raiz
        {
            Nodo* nuevoNodo = new Nodo(grado, false);
            nuevoNodo->setHijoInPos(0, raiz);
            nuevoNodo->splitHijo(0, raiz);
            int index = 0;
            if (convertToDate(nuevoNodo->getClaveInPos(0)->expiry_date) < convertToDate(producto->expiry_date))
            {
                index+= 1;
            }
            nuevoNodo->getHijoInPos(index)->insertarEnParcial(producto);
            this->raiz = nuevoNodo;
        }
        else
        {
            this->raiz->insertarEnParcial(producto);
        }
    }
}

void ArbolB::eliminar(std::string barcode, std::string fechaExp)
{
    if (raiz == nullptr)
    {
        return;
    }

    this->raiz->eliminar(barcode, fechaExp);

    if (raiz->getNumClaves() == 0)
    {
        Nodo* aux = raiz;
        if (raiz->getIsHoja())
        {
            this->raiz = nullptr;
        }
        else
        {
            raiz = raiz->getHijoInPos(0);
        }
        delete aux;
    }
}
