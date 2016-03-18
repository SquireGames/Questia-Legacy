#include "Utl.h"

#include <stdlib.h>//std::atoi
#include <vector>

int utl::asNumber(std::string _string)
{
    return atoi(_string.c_str());
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
    for(int it = 0; it != stringParts.size(); it++)
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
