//
// Created by yaxkin on 3/24/26.
//
#include "./clases/Product.h"
#include "./tads/NodoAVL.h"
#include "./tads/NodoLista.h"
#include "./tads/ArbolAVL.h"
#include "./tads/Lista.h"
#include "../globals.h"
#include "./loader.h"
#include <vector>
#include <iostream>

// -------------------- Carga a las estructuras
void loader(std::vector<Product>& listaProductos)
{
        std::cout << "Cargando a las estructuras..." << std::endl;

        for (Product& p : listaProductos)
        {
            Product* productoCopia = new Product(p);
            Product* productoCopia2 = new Product(p);
            Product* productoCopia3 = new Product(p);
            NodoAVL* nodoAVL = new NodoAVL(productoCopia);
            NodoLista* nodoLista1 = new NodoLista(productoCopia2);
            NodoLista* nodoLista2 = new NodoLista(productoCopia3);
            // TODO Aquí se insertaría nodoAVL en el árbol AVL y nodoLista en la lista
            // Por ejemplo:
            arbolAVL->agregarNodo(nodoAVL, arbolAVL->getRaiz());
            listaDesordenada->agregarSiguiente(nodoLista1);
            listaOrdenada->agregarSiguiente(nodoLista2);
        }
}