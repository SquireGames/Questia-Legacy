#ifndef UTL_H
#define UTL_H

#include <string>
#include <sstream>
#include <vector>

#include <boost/algorithm/string.hpp>

namespace utl
{
enum Direction {none = 0, up = 1, upRight = 2, right = 3, downRight = 4, down = 5, downLeft = 6, left = 7, upLeft = 8};

int asInt(const std::string& _string);
float asFloat(const std::string& _string);

bool isNumber(const std::string& _string);
bool isWithAnyCharacter(const std::string& _string, const std::string& characters);

std::vector <std::string> separateString (std::string saveString, char delimiter);
std::vector <std::string> separateString (std::string saveString, std::string delimiters);
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

struct Vector2i
{
    Vector2i() : x(0), y(0) {}
    Vector2i(int _x, int _y): x(_x), y(_y) {}
    int x, y;
};
struct Vector2ui
{
    Vector2ui() : x(0), y(0) {}
    Vector2ui(unsigned int _x, unsigned int _y): x(_x), y(_y) {}
    unsigned int x, y;
};

struct IntRect
{
    IntRect() = default;
    IntRect(int _x, int _y,int _width,int _height) : x(_x), y(_y), width(_width), height(_height) {}

    int x, y, width, height;
};

}

#endif // UTL_H
