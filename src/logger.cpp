#include "logger.h"

#include <fstream>
#include <ctime>
#include <iomanip>

void Logger::log(const std::string& message)
{
    std::ofstream logFile("log.txt", std::ios::app);

    if (!logFile)
        return;

    time_t now = time(nullptr);

    tm *local = localtime(&now);

    logFile << "["
            << std::put_time(local, "%Y-%m-%d %H:%M:%S")
            << "] "
            << message
            << std::endl;

    logFile.close();
}
