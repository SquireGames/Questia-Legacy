#ifndef VECTOR2_H
#define VECTOR2_H

namespace utl
{
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
struct Vector2f
{
    Vector2f() : x(0), y(0) {}
    Vector2f(float _x, float _y): x(_x), y(_y) {}
    float x, y;
};
}
#endif // VECTOR2_H
