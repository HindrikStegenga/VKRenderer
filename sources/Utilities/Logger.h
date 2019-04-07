//
// Created by Hindrik Stegenga on 29-10-17.
//

#ifndef VKRENDERER_LOGGER_H
#define VKRENDERER_LOGGER_H

#include <string>
#include <iostream>
#include <sstream>
#include <fstream>

using std::ostream;
using std::cout;
using std::cin;
using std::endl;
using std::string;

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


enum class LogLevel : char
{
    Succes,
    Information,
    Warning,
    Error,
    Failure,
};

inline string tagged(LogLevel l, const string& value, bool isColorized = false)
{
    string       level;
    string       modifier;
    switch(l)
    {
        case LogLevel::Information:
            modifier = BOLDCYAN;
            level = "   INFO  ";
            break;
        case LogLevel::Warning:
            modifier = BOLDYELLOW;

            level = " WARNING ";
            break;
        case LogLevel::Error:
            modifier = BOLDRED;
            level = "  ERROR  ";
            break;
        case LogLevel::Succes:
            modifier = BOLDGREEN;
            level = " SUCCESS ";
            break;
        case LogLevel::Failure:
            modifier = BOLDBLUE;
            level = " FAILURE ";;
    }

    std::stringstream str;
    if(isColorized)
        str << WHITE << "[" << modifier << level << WHITE << "]" << "\t" << value;
    else
        str << "[" << level << "]" << "\t" << value;


    return str.str();
}

class Logger
{
private:
    static bool logToFile;
    static bool logFileIsOpened;

public:
    Logger() = default;
    ~Logger() = default;

    Logger(const Logger&) = delete;
    Logger(Logger&&) = delete;

    Logger& operator=(const Logger&) = delete;
    Logger& operator=(const Logger&&) = delete;


    static void log(const string& msg);
    static void warn(const string& msg);
    static void error(const string& msg);
    static void success(const string& msg);
    static void failure(const string& msg);

    static void logNoEndl(const string& msg);
    static void warnNoEndl(const string& msg);
    static void errorNoEndl(const string& msg);
    static void successNoEndl(const string& msg);
    static void failureNoEndl(const string& msg);

private:
    static void logToFileAndConsole(const string& msg, LogLevel e);
};

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


#endif //VKRENDERER_LOGGER_H
