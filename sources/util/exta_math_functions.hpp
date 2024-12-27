#ifndef EXTRA_MATH_FUNCTIONS_HPP
#define EXTRA_MATH_FUNCTIONS_HPP

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
} // namespace utl

#endif // EXTRA_MATH_FUNCTIONS_HPP