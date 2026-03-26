//
// Created by yaxkin on 3/24/26.
//

#include "../tads/ArbolAVL.h"

ArbolAVL::ArbolAVL(NodoAVL* rz)
{
    this->raiz = rz;
}

ArbolAVL::~ArbolAVL()
{
    delete this->raiz;
}

NodoAVL* ArbolAVL::getRaiz()
{
    return this->raiz;
}

void ArbolAVL::setRaiz(NodoAVL* rz)
{
    this->raiz = rz;
}

void ArbolAVL::agregarNodo(NodoAVL* nodo, NodoAVL* rz)
{
    if (rz == nullptr)
    {
        this->raiz = nodo;
        return;
    }
    valorAZ orden = valorOrdenarAZ(nodo->getValor()->name, rz->getValor()->name);
    if (orden == valorAZ::izquierda)
    {
        if (rz->getIzquierdo() == nullptr)
        {
            rz->setIzquierdo(nodo);
        }
        else
        {
            agregarNodo(nodo, rz->getIzquierdo());
        }
    }
    else if (orden == valorAZ::derecha)
    {
        if (rz->getDerecho() == nullptr)
        {
            rz->setDerecho(nodo);
        }
        else
        {
            agregarNodo(nodo, rz->getDerecho());
        }
    }
    else
    {
        std::cout << "Valor duplicado, se descarta el producto" << std::endl;
        //TODO: agregar al log, flag de insercion fallida (para hacer rollback)
        delete nodo;
    }
}

void ArbolAVL::balancear(NodoAVL* rz)
{
    //todo implementar metodos de balanceo
}

void ArbolAVL::listarInorder(Nodo* rz)
{
    if (rz == nullptr) return;

    listarInorder(rz->getIzquierdo());
    std::cout << rz->getValor()->barcode << " - " << rz->getValor()->name << std::endl;
    listarInorder(rz->getDerecho());
}


