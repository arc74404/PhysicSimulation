#ifndef DEF_SCOPE_HPP
#define DEF_SCOPE_HPP

#include <initializer_list>

namespace sml
{
struct DefScope
{
    template <typename T>
    constexpr DefScope(T xx_min, T xx_max) noexcept
        : x_min(static_cast<float>(xx_min)), x_max(static_cast<float>(xx_max))
    {
        if (x_min > x_max) std::swap(x_min, x_max);
    }
    template <typename T>
    constexpr DefScope(std::initializer_list<T> init_list) noexcept
        : DefScope(*init_list.begin(), *init_list.end())
    {
    }
    float x_min;
    float x_max;
};
} // namespace sml

#endif // !DEF_SCOPE
