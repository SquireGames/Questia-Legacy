#include "Utl/Utl.h"

#include <stdlib.h>//std::atoi
#include <vector>

float utl::asFloat(const std::string& _string)
{
    return atoi(_string.c_str());
}

int utl::asInt(const std::string& _string)
{
    return atoi(_string.c_str());
}

bool utl::isNumber(const std::string& _string)
{
    return (_string.find_first_not_of("0123456789.-") == std::string::npos);
}

std::vector <std::string> utl::separateString (std::string saveString, char delimiter)
{
    std::stringstream sStream;
    std::vector <std::string> returnVector;
    sStream << saveString;
    while (sStream.good())
    {
        std::string entry;
        std::getline(sStream, entry, delimiter);
        returnVector.push_back(entry);
    }
    return returnVector;
}

std::string utl::conjoinString (std::vector <std::string> stringParts, char delimiter)
{
    std::stringstream sStream;
    for(unsigned int it = 0; it != stringParts.size(); it++)
    {
        sStream << stringParts[it];
        if(it != stringParts.size()-1)
        {
            sStream << delimiter;
        }
    }
    std::string conjoinedString = sStream.str();
    return conjoinedString;
}

std::string utl::conjoinString (std::vector <std::string> stringParts)
{
    std::stringstream sStream;
    for(unsigned int it = 0; it != stringParts.size(); it++)
    {
        sStream << stringParts[it];
    }
    std::string conjoinedString = sStream.str();
    return conjoinedString;
}
