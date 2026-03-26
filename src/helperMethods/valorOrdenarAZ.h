//
// Created by yaxkin on 3/25/26.
//

#ifndef ARBOLES_VALORORDENARAZ_H
#define ARBOLES_VALORORDENARAZ_H
#include <string>

enum class valorAZ
{
    izquierda,
    derecha,
    duplicado
};

valorAZ valorOrdenarAZ(std::string aInsertar, std::string refRaiz);

#endif //ARBOLES_VALORORDENARAZ_H