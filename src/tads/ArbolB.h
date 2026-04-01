//
// Created by yaxkin on 3/29/26.
//

#ifndef ARBOLES_ARBOLB_H
#define ARBOLES_ARBOLB_H

#include "tads/NodoB.h"
#include "clases/Product.h"

class ArbolB
{
    using Nodo = NodoB;
private:
    Nodo* raiz;
    int grado;

public:
    ArbolB(int grad);
    ~ArbolB();

    void recorrer();
    Nodo* getRaiz();

    Product* buscar(std::string fechaExp);
    void insertar(Product* producto);
    void eliminar(std::string barcode, std::string fechaExp);
};


#endif //ARBOLES_ARBOLB_H