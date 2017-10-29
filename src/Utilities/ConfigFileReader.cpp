//
// Created by Hindrik Stegenga on 29-10-17.
//

#include "ConfigFileReader.h"

std::string getCurrentWorkingDir()
{
    char buff[FILENAME_MAX];
    void* c = GetCurrentDir( buff, FILENAME_MAX );
    if(c == nullptr)
        Logger::failure("Error getting working directory!");
    std::string current_working_dir(buff);
    return current_working_dir;
}

void ConfigFileReader::parseFile(string file)
{
    std::ifstream configFile(file);
    std::string line;
    std::regex match("([a-zA-Z]+)\\s*=\\s*([a-zA-Z0-9]+)");

    if(!configFile.is_open())
    {
        Logger::failure("Cannot read config file: " + file);
    }

    while(std::getline(configFile, line))
    {
        std::smatch matchresults;
        if(std::regex_match(line, matchresults, match))
        {
            m_Values.insert(std::pair<std::string, std::string>(matchresults[1], matchresults[2]));
        }
    }
    configFile.close();
}

ConfigFileReader::ConfigFileReader(bool pwd)
{
    if (pwd) {
        Logger::log("Current working directory is: " + getCurrentWorkingDir());
    }
}

const std::map<string, string>& ConfigFileReader::map() const
{
    return m_Values;
}