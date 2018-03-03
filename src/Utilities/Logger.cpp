//
// Created by Hindrik Stegenga on 29-10-17.
//

#include "Logger.h"
#include <ctime>

#ifdef WIN32

#define RESET   ""
#define BLACK   ""
#define RED     ""
#define GREEN   ""
#define YELLOW  ""
#define BLUE    ""
#define MAGENTA ""
#define CYAN    ""
#define WHITE   ""
#define BOLDBLACK   ""
#define BOLDRED     ""
#define BOLDGREEN   ""
#define BOLDYELLOW  ""
#define BOLDBLUE    ""
#define BOLDMAGENTA ""
#define BOLDCYAN    ""
#define BOLDWHITE   ""

#else

#define RESET   "\033[0m"
#define BLACK   "\033[30m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"
#define WHITE   "\033[37m"
#define BOLDBLACK   "\033[1m\033[30m"
#define BOLDRED     "\033[1m\033[31m"
#define BOLDGREEN   "\033[1m\033[32m"
#define BOLDYELLOW  "\033[1m\033[33m"
#define BOLDBLUE    "\033[1m\033[34m"
#define BOLDMAGENTA "\033[1m\033[35m"
#define BOLDCYAN    "\033[1m\033[36m"
#define BOLDWHITE   "\033[1m\033[37m"

#endif

bool Logger::logToFile = true;
bool Logger::logFileIsOpened = false;

void Logger::log(string msg)
{
    std::stringstream str;
    str << msg << std::endl;
    logToFileAndConsole(str.str(), LogLevel::Information);
}

void Logger::warn(string msg)
{
    std::stringstream str;
    str << msg << std::endl;
    logToFileAndConsole(str.str(), LogLevel::Warning);
}

void Logger::error(string msg)
{
    std::stringstream str;
    str << msg << std::endl;
    logToFileAndConsole(str.str(), LogLevel::Error);

}

void Logger::succes(string msg)
{
    std::stringstream str;
    str << msg << std::endl;
    logToFileAndConsole(str.str(), LogLevel::Succes);
}

void Logger::failure(string msg)
{
    std::stringstream str;
    str << RED << msg << WHITE << std::endl;
    logToFileAndConsole(str.str(), LogLevel::Failure);
    throw std::runtime_error(msg);
}

void Logger::logNoEndl(string msg)
{
    logToFileAndConsole(move(msg), LogLevel::Information);
}

void Logger::warnNoEndl(string msg)
{
    logToFileAndConsole(move(msg), LogLevel::Warning);
}

void Logger::errorNoEndl(string msg)
{
    logToFileAndConsole(move(msg), LogLevel::Error);
}

void Logger::succesNoEndl(string msg)
{
    logToFileAndConsole(move(msg), LogLevel::Succes);
}

void Logger::failureNoEndl(string msg)
{
    string str = RED + msg + WHITE;

    logToFileAndConsole(str, LogLevel::Failure);
    throw std::runtime_error(msg);
}

void Logger::logToFileAndConsole(string str, LogLevel e)
{
    time_t currentTime;
    time(&currentTime);
    char timeString[9];
    struct tm* time_info;
    time_info = localtime(&currentTime);
    strftime(timeString, sizeof(timeString), "%H:%M:%S", time_info);
    string timestamp(timeString);

    cout << "[" << timestamp << "]" << tagged(e,str, true);
    if(!logToFile) return;

    std::ofstream ofs;

    if(logFileIsOpened)
        ofs.open("log.txt", std::ios_base::app);
    else
        ofs.open("log.txt", std::ios_base::trunc);

    if(ofs.is_open())
    {
        if(!logFileIsOpened)
        {
            ofs << "This log file has been created on " << ctime(&currentTime) << std::endl;

        }
        ofs << "[" << timestamp << "]" << tagged(e, str);
    }
    else
    {
        cout << "[" << timestamp << "]" << tagged(LogLevel::Error,"Could not open log file!", true);
    }
    logFileIsOpened = true;
    ofs.close();
}

#undef RESET
#undef BLACK
#undef RED
#undef GREEN
#undef YELLOW
#undef BLUE
#undef MAGENTA
#undef CYAN
#undef WHITE
#undef BOLDBLACK
#undef BOLDRED
#undef BOLDGREEN
#undef BOLDYELLOW
#undef BOLDBLUE
#undef BOLDMAGENTA
#undef BOLDCYAN
#undef BOLDWHITE