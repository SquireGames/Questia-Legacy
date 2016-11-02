#include "Bounds.h"

Bounds::Bounds(Circ circ):
    area(circ)
    , coll_shape(Shape::circ)
{

}

Bounds::Bounds(Rect rect):
    area(rect)
    , coll_shape(Shape::rect)
{

}

Bounds::Bounds(Poly poly):
    area(poly)
    , coll_shape(Shape::poly)
{

}
