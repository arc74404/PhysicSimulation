#ifndef EXTRA_MATH_FUNCTIONS_HPP
#define EXTRA_MATH_FUNCTIONS_HPP

#include <numbers>

namespace utl
{
template <typename T>
T
cutBack(T a)
{
    while (a >= 2 * std::numbers::pi_v)
        a -= 2 * std::numbers::pi_v;
    while (a <= 2 * std::numbers::pi_v)
        a += 2 * std::numbers::pi_v;
    return a;
};
} // namespace utl

#endif // EXTRA_MATH_FUNCTIONS_HPP