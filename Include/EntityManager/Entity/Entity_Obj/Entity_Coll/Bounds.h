#ifndef BOUNDS_H
#define BOUNDS_H

#include <boost/variant.hpp>
#include <vector>

#include "Vector2.h"

struct Circ
{
    Circ(float _radius):radius(_radius){}
    float radius;
};
struct Rect
{
    Rect(utl::Vector2f _origin, utl::Vector2f _dims):origin(_origin), dims(_dims){}
    utl::Vector2f origin;
    utl::Vector2f dims;
};
struct Poly
{
    Poly(utl::Vector2f _origin, float _angle, std::vector<utl::Vector2f> _points): origin(_origin), angle(_angle), points(_points){}
    utl::Vector2f origin;
    float angle;
    std::vector<utl::Vector2f> points;
};
struct Dot
{
    utl::Vector2f point;
};
struct None {};

class Bounds
{
public:
    Bounds(Circ circ);
    Bounds(Rect rect);
    Bounds(Poly poly);
    Bounds(Dot dot);
    Bounds();
private:
    enum class Shape{circ, rect, poly, dot, none};
    Shape coll_shape;

    utl::Vector2f rel_coords;
    float maxRadius;
    boost::variant<Circ, Rect, Poly, Dot, None> area;
};
#endif // BOUNDS_H
