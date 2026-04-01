//
// Created by yaxkin on 3/28/26.
//

#include "logger.h"
#include <fstream>
#include <filesystem>
#include <iostream>

logger::logger()
{
    this->loggedEvents = "";
}

logger::~logger()
{
}

void logger::addLog(std::string event)
{
    this->loggedEvents += event + "\n";
}

void logger::saveLogToFile(std::string filename)
{
    std::string dirSalida = "salidas/";
    std::filesystem::path dir(dirSalida);
    if (!std::filesystem::exists(dir))
    {
        std::filesystem::create_directories(dir);
    }

    std::string filePath = dirSalida + filename;
    std::ofstream out(filePath);
    if (!out.is_open())
    {
        std::cout << "Error: No se pudo abrir el archivo de log: " << filePath << std::endl;
        return;
    }

    out << loggedEvents;
    out.close();
    std::cout << "Log guardado en: " << filePath << std::endl;
}

void logger::logBadLine(std::string line, int idx)
{
    std::string logEntry = "Linea " + std::to_string(idx) + " no valida: " + line;
    addLog(logEntry);
}

void logger::logEvent(std::string event)
{
    addLog(event);
}

bool logger::isEmptyLog()
{
    return loggedEvents.empty();
}
