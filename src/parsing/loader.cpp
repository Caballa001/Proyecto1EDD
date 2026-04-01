//
// Created by yaxkin on 3/24/26.
//
#include "./clases/Product.h"
#include "./tads/NodoAVL.h"
#include "./tads/NodoLista.h"
#include "./tads/NodoB.h"
#include "./tads/ArbolAVL.h"
#include "./tads/Lista.h"
#include "./tads/ArbolB.h"
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
                loggerGlob->logEvent("Producto con barcode " + p.barcode + " ya existe, se descarta el producto");
                continue;
            }
            if (arbolAVL->buscarProductPorNombre(arbolAVL->getRaiz(), p.name) != nullptr)
            {
                loggerGlob->logEvent("Producto con nombre " + p.name + " ya existe en el arbol, se descarta el producto");
                continue;
            }

            Product* productoCopia = new Product(p);
            Product* productoCopia2 = new Product(p);
            Product* productoCopia3 = new Product(p);
            Product* productoCopia4 = new Product(p);

            NodoAVL* nodoAVL = new NodoAVL(productoCopia);
            NodoLista* nodoLista1 = new NodoLista(productoCopia2);
            NodoLista* nodoLista2 = new NodoLista(productoCopia3);


            //auto timeIni = std::chrono::high_resolution_clock::now();
            arbolAVL->agregarNodo(nodoAVL, arbolAVL->getRaiz());
            //auto timeEnd = std::chrono::high_resolution_clock::now();
            //auto duracion = std::chrono::duration_cast<std::chrono::microseconds>(timeEnd - timeIni);
            //std::cout << "Tiempo de insercion en ArbolAVL: " << duracion.count() << " microsegundos (μs)" << std::endl;

            //timeIni = std::chrono::high_resolution_clock::now();
            listaDesordenada->agregar(nodoLista1);
            //timeEnd = std::chrono::high_resolution_clock::now();
            //duracion = std::chrono::duration_cast<std::chrono::microseconds>(timeEnd - timeIni);
            //std::cout << "Tiempo de insercion en lista desordenada: " << duracion.count() << " microsegundos (μs)" << std::endl;

            //timeIni = std::chrono::high_resolution_clock::now();
            listaOrdenada->agregarEnOrden(nodoLista2);
            //timeEnd = std::chrono::high_resolution_clock::now();
            //duracion = std::chrono::duration_cast<std::chrono::microseconds>(timeEnd - timeIni);
            //std::cout << "Tiempo de insercion en lista ordenada: " << duracion.count() << " microsegundos (μs)" << std::endl;

            arbolB->insertar(productoCopia4);

            arbolAVL->setRaiz(arbolAVL->checkBalance(arbolAVL->getRaiz()));
        }


}