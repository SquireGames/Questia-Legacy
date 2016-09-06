#ifndef RECT_H
#define RECT_H

namespace utl
{
struct IntRect
{
    IntRect() = default;
    IntRect(int _x, int _y,int _width,int _height) : x(_x), y(_y), width(_width), height(_height) {}
    int x, y, width, height;
};
}

#endif // RECT_H
