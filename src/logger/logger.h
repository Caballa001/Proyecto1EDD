//
// Created by yaxkin on 3/28/26.
//

#ifndef ARBOLES_LOGGER_H
#define ARBOLES_LOGGER_H
#include <string>


class logger
{
private:
    std::string loggedEvents;
public:
    logger();
    ~logger();
    void addLog(std::string event);
    void getLog();
    void saveLogToFile(std::string filename);
    void logBadLine(std::string line, int idx);
    void logEvent(std::string event);
    bool isEmptyLog();
};


#endif //ARBOLES_LOGGER_H