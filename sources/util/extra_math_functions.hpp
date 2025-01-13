#ifndef EXTRA_MATH_FUNCTIONS_HPP
#define EXTRA_MATH_FUNCTIONS_HPP

#include <SFML/System/Vector2.hpp>

#include <numbers>

namespace utl
{
template <typename T>
T
cutBack(T a)
{
    while (a >= 2 * std::numbers::pi_v<float>)
        a -= 2 * std::numbers::pi_v<float>;
    while (a <= 2 * std::numbers::pi_v<float>)
        a += 2 * std::numbers::pi_v<float>;
    return a;
};

using Point = sf::Vector2f;

bool
isPointsEqual(const utl::Point& left, const utl::Point& right);

bool
isFloatsEqual(float left, float right, int count_digits_after_dot = 5);

float
getLength(const sf::Vector2f& vec);

} // namespace utl

#endif // EXTRA_MATH_FUNCTIONS_HPP