#ifndef Y_LIMIT_HPP
#define Y_LIMIT_HPP

#include <initializer_list>

namespace sml
{
struct YLimit
{
    template <typename T>
    constexpr YLimit(T yy_min, T yy_max) noexcept
        : y_min(static_cast<float>(yy_min)), y_max(static_cast<float>(yy_max))
    {
        if (y_min > y_max) std::swap(y_min, y_max);
    }
    template <typename T>
    constexpr YLimit(std::initializer_list<T> init_list) noexcept
        : YLimit(*init_list.begin(), *init_list.end())
    {
    }
    float y_min;
    float y_max;
};
} // namespace sml
#endif // !Y_LIMIT_HPP
