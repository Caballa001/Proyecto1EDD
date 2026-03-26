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

void generarDot(NodoAVL* nodo)
{
    std::string dotContent = "digraph AVL {\n";
    contenidoDigraph(nodo, dotContent);
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

void contenidoDigraph(NodoAVL* nodo, std::string& content)
{
    //preorder
    if (nodo == nullptr)
    {
        content.resize(content.size() - 4); // elimina " -> " suelto
        content += ";\n";
        return;
    }

    content += "\"" + nodo->getValor()->name + " - " + nodo->getValor()->barcode + "\"" + " -> ";
    contenidoDigraph(nodo->getIzquierdo(), content);
    content += "\"" + nodo->getValor()->name + " - " + nodo->getValor()->barcode + "\"" + " -> ";
    contenidoDigraph(nodo->getDerecho(), content);
}