//
// Created by yaxkin on 3/29/26.
//

#include "NodoB.h"

#include <iostream>
#include "helperMethods/helperMethods.h"
#include <chrono>

#include "globals.h"

NodoB::NodoB(int grad, bool hoja)
{
    this->grado = grad;
    this->isHoja = hoja;

    this->claves = new Product*[2 * grado - 1]; // Array de punteros de Productos
    this->hijos = new Nodo* [2 * grado]; //Array de punteros de hijos
    this->numClaves = 0;
}

NodoB::~NodoB()
{
    for (int i = 0; i < numClaves; i++)
    {
        delete this->claves[i];
    }
    delete[] this->claves;

    if (!isHoja)
    {
        for (int i = 0; i <= numClaves; i++)
        {
            delete this->hijos[i];
        }
    }
    delete[] this->hijos;
}

void NodoB::setClaveInPos(int pos, Product* producto)
{
    this->claves[pos] = producto;
}

void NodoB::setNumClaves(int numClaves)
{
    this->numClaves = numClaves;
}

void NodoB::setHijoInPos(int pos, Nodo* producto)
{
    this->hijos[pos] = producto;
}

int NodoB::getNumClaves()
{
    return this->numClaves;
}

Product* NodoB::getClaveInPos(int pos)
{
    return this->claves[pos];
}

NodoB::Nodo* NodoB::getHijoInPos(int pos)
{
    return this->hijos[pos];
}

bool NodoB::getIsHoja()
{
    return this->isHoja;
}

void NodoB::insertarEnParcial(Product*producto)
{
    // Seteamos hasta el tope
    int i = numClaves - 1;

    if (isHoja)
    {
        // Mientras las claves sean mayores, se corren una posicion a la derecha
        while (i >= 0 && convertToDate(claves[i]->expiry_date) > convertToDate(producto->expiry_date))
        {
            claves[i + 1] = claves[i];
            i--;
        }
        claves[i + 1] = producto;
        numClaves++;
    } else
    {
        while (i >= 0 && convertToDate(claves[i]->expiry_date) > convertToDate(producto->expiry_date))
        {
            i--;
        }
        // Si el hijo esta lleno lo partimos
        if (hijos[i+1]->numClaves == 2 * grado -1)
        {
            splitHijo(i+1, hijos[i+1]);
            // Si la clave mayor del original es menor, nos vamos al nuevo hijo
            if (convertToDate(claves[i+1]->expiry_date) < convertToDate(producto->expiry_date))
            {
                i++;
            }
        }
        hijos[i+1]->insertarEnParcial(producto);
    }
}

void NodoB::splitHijo(int posHijo, Nodo* nodo)
{
    Nodo* nuevoNodo = new Nodo(nodo->grado, nodo->isHoja);
    nuevoNodo->numClaves = grado - 1;

    // Copiamos la mitad derecha de las claves
    for (int i = 0; i < grado - 1; i++)
    {
        nuevoNodo->claves[i] = nodo->claves[i + grado];
    }

    // Si no es hoja, tambien nos llevamos la mitad de los hijos
    if (!nodo->isHoja)
    {
        for (int i = 0; i < grado; i++)
        {
            nuevoNodo->hijos[i] = nodo->hijos[i + grado];
            nodo->hijos[i + grado] = nullptr;
        }
    }


    nodo->numClaves = grado - 1;
    // Anula los pointers que fueron transferidos
    for (int i = grado; i < 2*grado -1; i++)
    {
        nodo->claves[i] = nullptr;
    }
    // Movemos a los hijos a la derecha
    for (int i = numClaves; i >= posHijo + 1; i--)
    {
        hijos[i+1] = hijos[i];
    }

    hijos[posHijo+1] = nuevoNodo;
    // Movemos las claves a la derecha
    for (int i = numClaves -1; i >= posHijo; i--)
    {
        claves[i+1] = claves[i];
    }

    // Promueve al medio y anula el pointer del original
    claves[posHijo] = nodo->claves[grado - 1];
    nodo->claves[grado - 1] = nullptr;

    numClaves++;
}

void NodoB::recorrer()
{
    //InOrder
    //Hijo1 - Clave1 - Hijo2 - Clave2 ... HijoN
    int i;
    for (i = 0; i < this->numClaves; i++)
    {
        if (!this->isHoja)
        {
            this->hijos[i]->recorrer();
        }
        std::cout << this->claves[i]->name << " - " << this->claves[i]->expiry_date << "- " << contadorNodo <<std::endl;
        contadorNodo++;
    }

    if (!this->isHoja)
    {
        this->hijos[i]->recorrer();
    }
}

Product* NodoB::buscar(std::string fechaExp)
{
    std::chrono::year_month_day fechaBuscar = convertToDate(fechaExp);
    int i = 0;
    // Avanzamos hasta que la fecha sea mayor que las claves
    while (i < this->numClaves && fechaBuscar > convertToDate(this->claves[i]->expiry_date) )
    {
        i++;
    }
    //Si hay match devolvemos el producto
    if (i < this->numClaves && convertToDate(this->claves[i]->expiry_date) == fechaBuscar)
    {
        return this->claves[i];
    }

    if (this->isHoja)
    {
        return nullptr;
    }
    //Entramos al hijo en esa posicion a seguir buscando un match
    return this->hijos[i]->buscar(fechaExp);
}

void NodoB::eliminar(std::string barcode, std::string fechaExp)
{
    // Pos de la primera clave >= a la fecha
    int idx = encontrarClave(convertToDate(fechaExp));
    int matchIdx =-1;
    // Si la fecha hace match compara codigos de barra
    for (int i = idx; i < numClaves && convertToDate(claves[i]->expiry_date) == convertToDate(fechaExp); i++)
    {
        if (claves[i]->barcode == barcode)
        {
            matchIdx = i;
            break;
        }
    }
    // La clave esta en el nodo
    if (matchIdx != -1)
    {
        // Se decide el caso
        if (isHoja)
        {
            eliminarDeHoja(matchIdx);
        } else
        {
            eliminarDeNodoInterno(barcode, matchIdx);
        }
    }
    // La clave no esta en el nodo
    else
    {
        if (isHoja)
        {
            std::cout << "ArbolB: El producto con barcode " << barcode << " no fue encontrado." << std::endl;
            return;
        }

        bool isUltimoHijo = (idx == numClaves);
        // Eliminar del hijo viola el size minimo, le agregamos
        if (hijos[idx]->numClaves < grado)
        {
            llenar(idx);
        }
        // Edge case: La manipulacion de nodos pudo haber tomado una clave de este nodo
        // Se corrio una pos el hijo al que deberiamos descender
        if (isUltimoHijo && idx > numClaves)
        {
            hijos[idx-1]->eliminar(barcode, fechaExp);
        }
        else
        {
            hijos[idx]->eliminar(barcode, fechaExp);
        }
    }
}

int NodoB::encontrarClave(std::chrono::year_month_day fechaExp)
{
    int idx = 0;
    while (idx < numClaves && convertToDate(claves[idx]->expiry_date) < fechaExp)
    {
        idx++;
    }
    return idx;
}

void NodoB::eliminarDeHoja(int index)
{
    delete claves[index]; // Borra los contenidos del nodo
    for (int i = index + 1; i < numClaves; i++)
    {
        claves[i-1] = claves[i];
    }
    numClaves--;
    claves[numClaves] = nullptr; // borra el pointer no accesible
}

void NodoB::eliminarDeNodoInterno(std::string barcode, int index)
{
    // Casos de eliminacion
    // Caso B-a tomamos predecesor del arbol izquierdo
    if (hijos[index]->numClaves >= grado)
    {
        Product* predecesor = getPredecesor(index);
        delete claves[index];
        claves[index] = new Product(*predecesor);
        hijos[index]->eliminar(predecesor->barcode, predecesor->expiry_date);
    }
    // Caso B-b tomamos del arbol derecho
    else if (hijos[index+1]->numClaves >= grado)
    {
        Product* sucesor = getSucesor(index);
        delete claves[index];
        claves[index] = new Product(*sucesor);
        hijos[index + 1]->eliminar(sucesor->barcode, sucesor->expiry_date);
    }
    // Caso B-c si tomar de uno de los dos viola el tamanio, los unimos y tomamos el medio
    else
    {
        std::string fechaExp = claves[index]->expiry_date;
        merge(index);
        // Descendemos y eliminamos del nuevo hijo unificado
        hijos[index]->eliminar(barcode, fechaExp);
    }
}

Product* NodoB::getPredecesor(int index)
{
    Nodo* actual = hijos[index];
    // Nos vamos al tope de la derecha del subarbol
    while (!actual->isHoja)
    {
        actual = actual->hijos[actual->numClaves];
    }
    // tomamos la ultima clave
    return actual->claves[actual->numClaves -1];
}

Product* NodoB::getSucesor(int index)
{
    Nodo* actual = hijos[index + 1];
    // tope de la izq del subarbol
    while (!actual->isHoja)
    {
        actual = actual->hijos[0];
    }
    // tomamos la primera clave
    return actual->claves[0];
}

void NodoB::llenar(int index)
{
    // Para no violar el minimo al borrar, checamos si hay 'sobrante' en los hermanos
    if (index != 0 && hijos[index - 1]->numClaves >= grado)
    {
        tomarDeAnterior(index);
    }
    else if (index != numClaves && hijos[index + 1]->numClaves >= grado)
    {
        tomarDeSiguiente(index);
    }
    // Si no hay, unificamos
    else
    {
        if (index != numClaves)
        {
            // Unimos con hermano a la derecha
            merge(index);
        }
        else
        {
            // Unimos con hermano a la izquierda
            merge(index -1);
        }
    }
}

void NodoB::tomarDeAnterior(int index)
{
    Nodo* hijo = hijos[index];
    Nodo* hermano = hijos[index - 1];

    // Corremos las claves a la derecha
    for (int i = hijo->numClaves-1; i >= 0; i--)
    {
        hijo->claves[i+1] = hijo->claves[i];
    }
    // Si hay hijos, tambien los corremos
    if (!hijo->isHoja)
    {
        for (int i = hijo->numClaves; i >= 0; i--)
        {
            hijo->hijos[i+1] = hijo->hijos[i];
        }
    }
    // Metemos la clave del padre en el hijo
    hijo->claves[0] = claves[index -1];

    // el ultimo hijo del hermano se vuelve el primero de este nodo hijo
    if (!hijo->isHoja)
    {
        hijo->hijos[0] = hermano->hijos[hermano->numClaves];
    }
    // La ultima clave del hermano se sube al padre para tomar el lugar de la clave que que bajamos
    claves[index -1] = hermano->claves[hermano->numClaves -1];

    hijo->numClaves++;
    hermano->numClaves--;
    hermano->claves[hermano->numClaves] = nullptr; // null el pointer del hermano
}

void NodoB::tomarDeSiguiente(int index)
{
    Nodo* hijo = hijos[index];
    Nodo* hermano = hijos[index +1];
    // Bajamos la clave al hijo y la ponemos al final
    hijo->claves[hijo->numClaves] = claves[index];
    // Tomamos al primer hijo del hermano y lo convertimos en el ultimo hijo del hijo
    if (!hijo->isHoja)
    {
        hijo->hijos[hijo->numClaves+1] = hermano->hijos[0];
    }
    // La primera clave del hermano se sube al padre para tomar el lugar de la clave que que bajamos
    claves[index] = hermano->claves[0];
    // Corremos las claves del hermano a la izquierda
    for (int i = 1; i < hermano->numClaves; i++)
    {
        hermano->claves[i-1] = hermano->claves[i];
    }
    // Corremos los punteros de los hijos
    if (!hermano->isHoja)
    {
        for (int i = 1; i <= hermano->numClaves; i++)
        {
            hermano->hijos[i - 1] = hermano->hijos[i];
        }
    }

    hijo->numClaves++;
    hermano->numClaves--;
    hermano->claves[hermano->numClaves] = nullptr; // null el pointer del hermano
}

void NodoB::merge(int index)
{
    Nodo* hijo = hijos[index];
    Nodo* hermano = hijos[index + 1];

    // Bajamos la clave del padre al hijo, poniendola en el medio
    hijo->claves[grado -1] = claves[index];

    // Copiamos claves del hermano al hijo en la derecha
    for (int i = 0; i < hermano->numClaves; i++)
    {
        hijo->claves[i + grado] = hermano->claves[i];
        hermano->claves[i] = nullptr; // nulleamos los ptr del hermano
    }

    // Si hay hijos los pasamos tambien
    if (!hijo->isHoja)
    {
        for (int i = 0; i <= hermano->numClaves; i++)
        {
            hijo->hijos[i+grado] = hermano->hijos[i];
        }
    }
    // Movemos las claves del padre a la izq
    for (int i = index + 1; i < this->numClaves; i++)
    {
        this->claves[i-1] = claves[i];
    }
    // movemos los hijos a la derecha
    for (int i = index + 2; i <= this->numClaves; i++)
    {
        this->hijos[i-1] = hijos[i];
    }

    hijo->numClaves += hermano->numClaves + 1;
    numClaves--;
    claves[numClaves] = nullptr; // null el ptr a la clave ascendida

    delete hermano;
}
