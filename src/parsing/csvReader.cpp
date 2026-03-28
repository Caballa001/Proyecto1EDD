//
// Created by yaxkin on 3/22/26.
//
#include <fstream>
#include <sstream>
#include <string>
#include <iostream>
#include <vector>
#include <filesystem>
#include "../clases/Product.h"
#include "./csvReader.h"

//----------------------- Helper

std::string trim (std::string& strTrim)
{
    std::string enBlanco = " \n\r\t\f\v";
    size_t posPrimerChar = strTrim.find_first_not_of(enBlanco);
    if (std::string::npos == posPrimerChar)
    {
        return "";
    }
    size_t posLastChar = strTrim.find_last_not_of(enBlanco);
    return strTrim.substr(posPrimerChar, (posLastChar - posPrimerChar + 1));
}

// -------------------------- Parseo de contenido

std::vector<std::string> splitCSVLine(const std::string& line)
{
    std::vector<std::string> fields;
    std::string field;
    bool entreComillas = false;

    for (size_t i = 0; i < line.size(); ++i)
    {
        char ch = line[i];
        if (ch == '"')
        {
            if (entreComillas && i + 1 < line.size() && line[i + 1] == '"')
            {
                ++i;
            }
            else
            {
                entreComillas = !entreComillas;
            }
        }
        else if (ch == ',' && !entreComillas)
        {
            fields.push_back(field);
            field.clear();
        }
        else
        {
            field += ch;
        }
    }
    fields.push_back(field); // last field
    return fields;
}

std::vector<Product> parseCSV(std::string& content)
{
    std::cout << "Parseando CSV... \n";

    std::vector<Product> products;
    std::istringstream stream(content);
    std::string line;

    std::getline(stream, line); // skip header row

    while (std::getline(stream, line))
    {
        // strip Windows-style \r if present
        if (!line.empty() && line.back() == '\r')
            line.pop_back();

        if (line.empty()) continue;

        std::vector<std::string> fields = splitCSVLine(line);

        if (fields.size() != 7) continue; // skip malformed lines

        Product p;
        p.name = fields[0];
        p.barcode = fields[1];
        p.category = fields[2];
        p.expiry_date = fields[3];
        p.brand = fields[4];
        p.price = std::stod(fields[5]);
        p.stock = std::stoi(fields[6]);

        products.push_back(p);
    }

    return products;
}

// ---------------------- Carga de Archivo

std::vector<Product> loadFile(std::string& path)
{
    std::ifstream file(path);

    if (!file.is_open())
    {
        std::cout << "No se pudo abrir el archivo: " << path << std::endl;
        return {};
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    file.close();
    std::string contentBuffer = buffer.str();

    return parseCSV(contentBuffer);

}

std::vector<Product> csvReader()
{
    std::cout << "Ingrese la dirección del archivo: ";
    std::string path;
    std::getline(std::cin, path);
    path = trim(path);
    if (path.empty())
    {
        std::cout << "La dirección del archivo no puede estar vacía." << std::endl;
        return {};
    }
    if (path.find(".csv") == std::string::npos)
    {
        std::cout << "El archivo debe tener extensión .csv" << std::endl;
        return {};
    }

    return loadFile(path);
}