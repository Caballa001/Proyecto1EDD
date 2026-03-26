//
// Created by yaxkin on 3/24/26.
//
#include <string>

#include "valorOrdenarAZ.h"

valorAZ valorOrdenarAZ(std::string aInsertar, std::string refRaiz)
{
    if (aInsertar < refRaiz)
    {
        return valorAZ::izquierda;
    }
    else if (aInsertar > refRaiz)
    {
        return valorAZ::derecha;
    }
    else
    {
        return valorAZ::duplicado;
    }
}
