#ifndef UTL_H
#define UTL_H

#include <string>
#include <sstream>
#include <vector>

namespace utl
{
    enum Direction {none = 0, up = 1, upRight = 2, right = 3, downRight = 4, down = 5, downLeft = 6, left = 7, upLeft = 8};

    int asInt(const std::string& _string);
    float asFloat(const std::string& _string);

    bool isNumber(const std::string& _string);

    std::vector <std::string> separateString (std::string saveString, char delimiter);
    std::string conjoinString (std::vector <std::string> stringParts, char delimiter);
    std::string conjoinString (std::vector <std::string> stringParts);

    template <class T>
    std::string asString (T _item)
    {
        std::stringstream ss;
        ss << _item;
        std::string item = ss.str();
        return item;
    }
}

#endif // UTL_H
