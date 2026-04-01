//
// Created by yaxkin on 3/24/26.
//
#include <string>
#include <iostream>
#include <chrono>
#include <sstream>

#include "helperMethods.h"

// ---- String utilities ----

std::string trim(std::string& strTrim)
{
    std::string enBlanco = " \n\r\t\f\v";
    size_t posPrimerChar = strTrim.find_first_not_of(enBlanco);
    if (std::string::npos == posPrimerChar)
        return "";
    size_t posLastChar = strTrim.find_last_not_of(enBlanco);
    return strTrim.substr(posPrimerChar, (posLastChar - posPrimerChar + 1));
}

// ---- Input validation ----

bool inputIsInt(std::string str)
{
    if (str.empty()) return false;
    try
    {
        str = trim(str);
        if (str.empty()) return false;
        std::size_t pos;
        std::stoi(str, &pos);
        return pos == str.length();
    }
    catch (const std::invalid_argument&) { return false; }
    catch (const std::out_of_range&)     { return false; }
}

bool inputIsDouble(std::string str)
{
    if (str.empty()) return false;
    try
    {
        str = trim(str);
        if (str.empty()) return false;
        std::size_t pos;
        std::stod(str, &pos);
        return pos == str.length();
    }
    catch (const std::invalid_argument&) { return false; }
    catch (const std::out_of_range&)     { return false; }
}

bool inputIsDate(std::string str)
{
    str = trim(str);
    if (str.length() != 10)          return false;
    if (str[4] != '-' || str[7] != '-') return false;

    std::string yearStr  = str.substr(0, 4);
    std::string monthStr = str.substr(5, 2);
    std::string dayStr   = str.substr(8, 2);

    if (!inputIsInt(yearStr) || !inputIsInt(monthStr) || !inputIsInt(dayStr))
        return false;

    int month = std::stoi(monthStr);
    int day   = std::stoi(dayStr);

    if (month < 1 || month > 12) return false;
    if (day   < 1 || day   > 31) return false;

    return true;
}

// ---- Tree / date helpers ----

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

std::chrono::year_month_day convertToDate(std::string fecha)
{
    std::istringstream ss{fecha};

    std::chrono::sys_days days;
    ss >> std::chrono::parse("%F", days);

    if (!ss.fail())
    {
        std::chrono::year_month_day ymd{days};
        return ymd;
    }
    std::cout << "Fecha no valida: " << fecha << std::endl;
    return std::chrono::year_month_day{};
}