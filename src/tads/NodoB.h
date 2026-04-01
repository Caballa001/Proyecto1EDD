//
// Created by yaxkin on 3/29/26.
//

#ifndef ARBOLES_NODOB_H
#define ARBOLES_NODOB_H
#include "./clases/Product.h"
#include <chrono>


class NodoB
{
private:
    int grado;
    Product** claves;
    NodoB** hijos;
    int numClaves;
    bool isHoja;

public:
    using Nodo = NodoB;

    NodoB(int grad, bool hoja);
    ~NodoB();
    void setClaveInPos(int pos, Product* producto);
    void setNumClaves(int numClaves);
    void setHijoInPos(int pos, Nodo* producto);
    int getNumClaves();
    Product* getClaveInPos(int pos);
    Nodo* getHijoInPos(int pos);
    bool getIsHoja();

    void insertarEnParcial(Product* producto);
    void splitHijo(int posHijo, Nodo* nodo);
    void recorrer();
    Product* buscar(std::string fechaExp);
    //TODO seguir
    void eliminar(std::string barcode, std::string fechaExp);

    int encontrarClave(std::chrono::year_month_day fechaExp);
    void eliminarDeHoja(int index);
    void eliminarDeNodoInterno(std::string barcode,int index);
    Product* getPredecesor(int index);
    Product* getSucesor(int index);
    void llenar(int index);
    void tomarDeAnterior(int index);
    void tomarDeSiguiente(int index);
    void merge(int index);
};


#endif //ARBOLES_NODOB_H