#include "extra_math_functions.hpp"

#include <cmath>

bool
utl::isPointsEqual(const Point& left, const Point& right)
{
    return left.x < (right.x + 0.00001f) && left.x > (right.x - 0.00001f) &&
           left.y < (right.y + 0.00001f) && left.y > (right.y - 0.00001f);
}

bool
utl::isFloatsEqual(float left, float right, int count_digits_after_dot)
{
    float d = 1 / std::pow(10, count_digits_after_dot);
    return (right - d) < left && left < (right + d);
}
