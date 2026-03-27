//
// Created by yaxkin on 3/24/26.
//

#ifndef ARBOLES_NODOAVL_H
#define ARBOLES_NODOAVL_H
#include "clases/Product.h"

class NodoAVL
{
private:
    Product* valor;
    int FactorBalance;
    NodoAVL* izquierdo;
    NodoAVL* derecho;
public:
    NodoAVL(Product* val);
    ~NodoAVL();

    Product* getValor();
    void setValor(Product* val);

    int getFactorBalance();
    void setFactorBalance(int fb);


    NodoAVL* getIzquierdo();
    void setIzquierdo(NodoAVL* hijo);

    NodoAVL* getDerecho();
    void setDerecho(NodoAVL* hijo);
};

#endif //ARBOLES_NODOAVL_H

