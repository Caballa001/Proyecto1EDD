//
// Created by yaxkin on 3/25/26.
//

#include "generarDot.h"
#include <string>
#include <fstream>
#include <cstdlib>
#include <iostream>
#include <vector>
#include <filesystem>

#include "globals.h"

void checkDirectoryExists(const std::string& path)
{
    std::filesystem::path dir(path);
    if (!std::filesystem::exists(dir))
    {
        std::filesystem::create_directories(dir);
        std::cout << "Directorio creado: " << path << std::endl;
    }
    else
    {
        std::cout << "Directorio ya existe: " << path << std::endl;
    }
}

void generarDotAVL(NodoAVL* nodo)
{
    std::string dotContent = "digraph AVL {\n";
    contenidoAVL(nodo, dotContent);
    /*
     * A -> B
     * A -> C
     * B -> D
     * B -> F
     * ...
     */
    dotContent += " }\n";

    std::string dirSalida = "salidas/";
    checkDirectoryExists(dirSalida);

    std::string dotPath = dirSalida + "ArbolAVL.dot";
    std::string pngPath = dirSalida + "ArbolAVL.png";

    std::ofstream out(dotPath);
    if (!out.is_open())
    {
        std::cout << "Error: No se pudo abrir el archivo: " << dotPath << std::endl;
        return;
    }
    out << dotContent;
    out.close();

    std::string cmd = "dot -Tpng " + dotPath + " -o " + pngPath;
    system(cmd.c_str());

}

void contenidoAVL(NodoAVL* nodo, std::string& content)
{
    //preorder
    if (nodo == nullptr)
    {
        return;
    }

    content += "\"" + nodo->getValor()->name + " - " + nodo->getValor()->barcode + "\"" + " -> ";
    if (nodo->getIzquierdo() != nullptr)
    {
        content += "\"" + nodo->getIzquierdo()->getValor()->name + " - " + nodo->getIzquierdo()->getValor()->barcode + "\"" + ";\n";
    }
    else
    {
        content.resize(content.size() - (9 + nodo->getValor()->name.size() + nodo->getValor()->barcode.size())); // elimina linea sin hijo
    }
    contenidoAVL(nodo->getIzquierdo(), content);
    content += "\"" + nodo->getValor()->name + " - " + nodo->getValor()->barcode + "\"" + " -> ";
    if (nodo->getDerecho() != nullptr)
    {
        content += "\"" + nodo->getDerecho()->getValor()->name + " - " + nodo->getDerecho()->getValor()->barcode + "\"" + ";\n";
    }
    else
    {
        content.resize(content.size() - (9 + nodo->getValor()->name.size() + nodo->getValor()->barcode.size())); // elimina linea sin hijo
    }
    contenidoAVL(nodo->getDerecho(), content);
}

void generarDotBtree(NodoB* nodo)
{
    std::string dotContent = "digraph Btree {\n"
                             "node[shape=record, height = 0.1];\n";
    contadorNodo = 0;
    contadorCells = 0;
    nodosBtree(nodo, dotContent);
    contadorCells = 0;
    contadorNodo = 0;
    contadorProductos = 0;
    conexionesBtree(nodo, dotContent);
    /*
     * Estructura del Btree
     */
    dotContent += " }\n";
    std::cout << contadorProductos << " productos recorridos" << std::endl;
    std::string dirSalida = "salidas/";
    checkDirectoryExists(dirSalida);

    std::string dotPath = dirSalida + "ArbolB.dot";
    std::string pngPath = dirSalida + "ArbolB.png";

    std::ofstream out(dotPath);
    if (!out.is_open())
    {
        std::cout << "Error: No se pudo abrir el archivo: " << dotPath << std::endl;
        return;
    }
    out << dotContent;
    out.close();

    std::string cmd = "dot -Tpng " + dotPath + " -o " + pngPath;
    system(cmd.c_str());
}

void nodosBtree(NodoB* nodo, std::string& content)
{
    if (nodo == nullptr)
    {
        contadorNodo = 0;
        return;
    }
    //Preorder
    content += "node" + std::to_string(contadorNodo) + " [label=\"";
    for (int i = 0; i < nodo->getNumClaves(); i++)
    {
        if (i==0)
        {
            content += "<f" + std::to_string(contadorCells) + ">" + " | ";
        }
        else
        {
            content += "| <f" + std::to_string(contadorCells) + "> | ";
        }
        contadorCells++;

        content += nodo->getClaveInPos(i)->name + " - " + nodo->getClaveInPos(i)->expiry_date + " ";
        contadorProductos++;
    }
    content += "| <f" + std::to_string(contadorCells) + ">\"];\n";
    contadorCells++;
    contadorNodo++;

    for (int i = 0; i <= nodo->getNumClaves(); i++)
    {
        if (!nodo->getIsHoja())
        {
            nodosBtree(nodo->getHijoInPos(i), content);
        }
    }
}

void conexionesBtree(NodoB* nodo, std::string& content)
{
    if (nodo == nullptr)
    {
        return;
    }

    //Preorder, al entrar a un ciclo pide el Num de nodo (padre) y celda inicial
    int localNode = contadorNodo;
    int localCellIni = contadorCells;

    contadorNodo++;
    contadorCells += nodo->getNumClaves() + 1; //Avanzar hasta el fN de ese nodo, y luego 1 mas del siguiente (hijo)

    for (int i = 0; i <= nodo->getNumClaves(); i++)
    {
        if (!nodo->getIsHoja())
        {
            int localNodeHijo = contadorNodo; //Nodo hijo 'nodeN'
            content += "node" + std::to_string(localNode) + ":f" + std::to_string(localCellIni + i) + " -> node" + std::to_string(localNodeHijo) + ";\n";
            conexionesBtree(nodo->getHijoInPos(i), content);
        }
    }
}

