//
// Created by yaxkin on 3/25/26.
//

#ifndef ARBOLES_VALORORDENARAZ_H
#define ARBOLES_VALORORDENARAZ_H
#include <string>
#include <chrono>

enum class valorAZ
{
    izquierda,
    derecha,
    duplicado
};

std::string trim(std::string& str);
bool inputIsInt(std::string str);
bool inputIsDouble(std::string str);
bool inputIsDate(std::string str);

valorAZ valorOrdenarAZ(std::string aInsertar, std::string refRaiz);

std::chrono::year_month_day convertToDate(std::string fecha);
std::string convertToString(std::chrono::year_month_day fecha);

#endif //ARBOLES_VALORORDENARAZ_H