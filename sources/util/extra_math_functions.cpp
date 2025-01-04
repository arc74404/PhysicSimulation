#include "extra_math_functions.hpp"

bool
utl::isPointsEqual(const Point& left, const Point& right)
{
    return left.x < (right.x + 0.00001f) && left.x > (right.x - 0.00001f) &&
           left.y < (right.y + 0.00001f) && left.y > (right.y - 0.00001f);
}

bool
utl::isFloatsEqual(float left, float right)
{
    return (right - 0.000001f) < left && left < (right + 0.000001f);
}
