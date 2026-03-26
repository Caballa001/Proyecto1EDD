//
// Created by yaxkin on 3/24/26.
//

#include "../tads/NodoAVL.h"

NodoAVL::NodoAVL(Product* val)
{
    this->valor = val;
    this->FactorBalance = 0;
    this->izquierdo = nullptr;
    this->derecho = nullptr;
}

NodoAVL::~NodoAVL()
{
    delete this->valor;
    this->FactorBalance = 0;
    delete this->izquierdo;
    delete this->derecho;
}

Product* NodoAVL::getValor()
{
    return this->valor;
}

void NodoAVL::setValor(Product* val)
{
    this->valor = val;
}

int NodoAVL::getFactorBalance()
{
    return this->FactorBalance;
}

void NodoAVL::setFactorBalance(int fb)
{
    this->FactorBalance = fb;
}

NodoAVL* NodoAVL::getIzquierdo()
{
    return this->izquierdo;
}

void NodoAVL::setIzquierdo(NodoAVL* hijo)
{
    this->izquierdo = hijo;
}

NodoAVL* NodoAVL::getDerecho()
{
    return this->derecho;
}

void NodoAVL::setDerecho(NodoAVL* hijo)
{
    this->derecho = hijo;
}
