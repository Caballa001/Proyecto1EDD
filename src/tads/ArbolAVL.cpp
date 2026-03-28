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
        std::cout << nodo->getValor()->name << " - " << rz->getValor()->name << std::endl;
        //TODO: agregar al log, flag de insercion fallida (para hacer rollback)
        delete nodo;
    }
}

int ArbolAVL::actualizarFB(Nodo* nodo)
{
    if (nodo == nullptr) return 0;
    int fb = obtenerAltura(nodo->getDerecho()) - obtenerAltura(nodo->getIzquierdo());
    nodo->setFactorBalance(fb);
    return fb;
}

int ArbolAVL::obtenerAltura(Nodo* nodo)
{
    if (nodo == nullptr) return -1;
    return std::max(obtenerAltura(nodo->getIzquierdo()), obtenerAltura(nodo->getDerecho())) + 1;
}

NodoAVL* ArbolAVL::checkBalance(NodoAVL* rz)
{
    if (rz == nullptr) return nullptr;

    // PostOrder: fix children first so heights are correct when we check this node
    rz->setIzquierdo(checkBalance(rz->getIzquierdo()));
    rz->setDerecho(checkBalance(rz->getDerecho()));

    actualizarFB(rz);
    if (rz->getFactorBalance() < -1)
    {
        actualizarFB(rz->getIzquierdo());
        if (rz->getIzquierdo()->getFactorBalance() <= 0)
        {
            rz = leftLeft(rz);
        }
        else
        {
            rz = leftRight(rz);
        }
        actualizarFB(rz);
    }
    else if (rz->getFactorBalance() > 1)
    {
        actualizarFB(rz->getDerecho());
        if (rz->getDerecho()->getFactorBalance() >= 0)
        {
            rz = rightRight(rz);
        }
        else
        {
            rz = rightLeft(rz);
        }
        actualizarFB(rz);
    }


    return rz;
}

NodoAVL* ArbolAVL::leftLeft(Nodo* rz)
{

    Nodo* nuevaRz = rz->getIzquierdo();
    rz->setIzquierdo(nuevaRz->getDerecho());
    nuevaRz->setDerecho(rz);

    actualizarFB(rz);
    actualizarFB(nuevaRz);

    return nuevaRz;
}

NodoAVL* ArbolAVL::rightRight(Nodo* rz)
{
    Nodo* nuevaRz = rz->getDerecho();
    rz->setDerecho(nuevaRz->getIzquierdo());
    nuevaRz->setIzquierdo(rz);

    actualizarFB(rz);
    actualizarFB(nuevaRz);

    return nuevaRz;
}

NodoAVL* ArbolAVL::leftRight(Nodo* rz)
{
    rz->setIzquierdo(rightRight(rz->getIzquierdo()));
    return leftLeft(rz);
}

NodoAVL* ArbolAVL::rightLeft(Nodo* rz)
{
    rz->setDerecho(leftLeft(rz->getDerecho()));
    return rightRight(rz);
}

Product* ArbolAVL::buscarProductPorNombre(Nodo* rz, std::string nombre)
{
    if (rz == nullptr) return nullptr;

    if (rz->getValor()->name == nombre)
        return rz->getValor();

    valorAZ orden = valorOrdenarAZ(nombre, rz->getValor()->name);
    if (orden == valorAZ::izquierda)
        return buscarProductPorNombre(rz->getIzquierdo(), nombre);
    if (orden == valorAZ::derecha)
        return buscarProductPorNombre(rz->getDerecho(), nombre);
    return rz->getValor();

    return nullptr;
}

std::string ArbolAVL::encontrarNombrePorBarcode(Nodo* rz, const std::string& barcode)
{
    if (rz == nullptr) return "";

    if (rz->getValor()->barcode == barcode)
        return rz->getValor()->name;

    std::string resultado = encontrarNombrePorBarcode(rz->getIzquierdo(), barcode);
    if (!resultado.empty()) return resultado;
    resultado =  encontrarNombrePorBarcode(rz->getDerecho(), barcode);
    return resultado;
}

NodoAVL* ArbolAVL::encontrarMinimo(Nodo* rz)
{
    Nodo* actual = rz;
    while (actual->getIzquierdo() != nullptr)
        actual = actual->getIzquierdo();
    return actual;
}

NodoAVL* ArbolAVL::eliminarPorNombre(Nodo* rz, const std::string& nombre)
{
    if (rz == nullptr) return nullptr;

    valorAZ orden = valorOrdenarAZ(nombre, rz->getValor()->name);
    if (orden == valorAZ::izquierda)
    {
        rz->setIzquierdo(eliminarPorNombre(rz->getIzquierdo(), nombre));
    }
    else if (orden == valorAZ::derecha)
    {
        rz->setDerecho(eliminarPorNombre(rz->getDerecho(), nombre));
    }
    else
    {
        // Casos posibles de hijos
        if (rz->getIzquierdo() == nullptr && rz->getDerecho() == nullptr)
        {
            delete rz;
            return nullptr;
        }
        else if (rz->getIzquierdo() == nullptr)
        {
            Nodo* temp = rz->getDerecho();
            rz->setDerecho(nullptr);
            delete rz;
            return temp;
        }
        else if (rz->getDerecho() == nullptr)
        {
            Nodo* temp = rz->getIzquierdo();
            rz->setIzquierdo(nullptr);
            delete rz;
            return temp;
        }
        else
        {
            Nodo* sucesor = encontrarMinimo(rz->getDerecho());
            std::string nombreSucesor = sucesor->getValor()->name;

            delete rz->getValor();
            rz->setValor(new Product(*sucesor->getValor()));

            rz->setDerecho(eliminarPorNombre(rz->getDerecho(), nombreSucesor));
        }
    }

    return rz;
}

void ArbolAVL::eliminarNodo(const std::string& nombre)
{
    if (buscarProductPorNombre(this->raiz, nombre) == nullptr)
    {
        std::cout << "Producto '" << nombre << "' no encontrado." << std::endl;
        return;
    }

    this->raiz = eliminarPorNombre(this->raiz, nombre);
    this->raiz = checkBalance(this->raiz);
}

void ArbolAVL::listarInorder(Nodo* rz)
{
    if (rz == nullptr) return;

    listarInorder(rz->getIzquierdo());
    std::cout << rz->getValor()->barcode << " - " << rz->getValor()->name << std::endl;
    listarInorder(rz->getDerecho());
}