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
            if (!listaDesordenada->isUnico(listaDesordenada->getCabeza(), p.barcode))
            {
                std::cout << "Producto con barcode " << p.barcode << " ya existe, se descarta el producto" << std::endl;
                continue;
            }
            if (arbolAVL->buscarProductPorNombre(arbolAVL->getRaiz(), p.name) != nullptr)
            {
                std::cout << "Producto con nombre " << p.name << " ya existe en el arbol, se descarta el producto" << std::endl;
                continue;
            }

            Product* productoCopia = new Product(p);
            Product* productoCopia2 = new Product(p);
            Product* productoCopia3 = new Product(p);
            NodoAVL* nodoAVL = new NodoAVL(productoCopia);
            NodoLista* nodoLista1 = new NodoLista(productoCopia2);
            NodoLista* nodoLista2 = new NodoLista(productoCopia3);

            arbolAVL->agregarNodo(nodoAVL, arbolAVL->getRaiz());
            listaDesordenada->agregar(nodoLista1);
            listaOrdenada->agregarEnOrden(nodoLista2);

            arbolAVL->setRaiz(arbolAVL->checkBalance(arbolAVL->getRaiz()));
        }


}