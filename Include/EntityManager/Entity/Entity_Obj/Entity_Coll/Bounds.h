#ifndef BOUNDS_H
#define BOUNDS_H

#include <boost/variant.hpp>
#include <vector>

#include "Vector2.h"

struct Circ
{
    float radius;
};
struct Rect
{
    utl::Vector2f origin;
    utl::Vector2f dims;
};
struct Poly
{
    utl::Vector2f origin;
    float angle;
    std::vector<utl::Vector2f> points;
};

class Bounds
{
public:
    Bounds(Circ circ);
    Bounds(Rect rect);
    Bounds(Poly poly);
private:
    enum class Shape{circ, rect, poly};
    Shape coll_shape;

    utl::Vector2f rel_coords;
    float maxRadius;
    boost::variant<Circ, Rect, Poly> area;
};
#endif // BOUNDS_H
