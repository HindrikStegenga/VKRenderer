//
// Created by Hindrik Stegenga on 29-10-17.
//

#ifndef VKRENDERER_CONFIGFILEREADER_H
#define VKRENDERER_CONFIGFILEREADER_H


#include <map>
#include <string>
#include <regex>
#include <fstream>

#ifdef _WIN32
#include <direct.h>
#define GetCurrentDir _getcwd
#else
#include <bits/ios_base.h>
#include <unistd.h>
#include <cstring>
#include "Logger.h"

#define GetCurrentDir getcwd
#endif

using std::string;

string getCurrentWorkingDir();

class ConfigFileReader final
{
private:
    std::map<string, string> m_Values;
public:
    explicit ConfigFileReader(bool pwd = false);
    ~ConfigFileReader() = default;

    ConfigFileReader(const ConfigFileReader&)   = default;
    ConfigFileReader(ConfigFileReader&&)        = default;

    ConfigFileReader& operator=(const ConfigFileReader&)    = default;
    ConfigFileReader& operator=(ConfigFileReader&&)         = default;
public:
    void parseFile(string file);
    const std::map<string,string>& map() const;

};


#endif //VKRENDERER_CONFIGFILEREADER_H
