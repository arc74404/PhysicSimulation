#ifndef BASE_BORDER_HPP
#define BASE_BORDER_HPP

#include <initializer_list>

namespace sml
{
class BaseBorder
{
public:
    enum class bType
    {
        LINEAR  = 0,
        X_CONST = 1
    };

    struct DefScope
    {
        constexpr DefScope(float xx1, float xx2) noexcept : x1(xx1), x2(xx2)
        {
        }
        constexpr DefScope(std::initializer_list<float> init_list) noexcept
            : x1(*init_list.begin()), x2(*(init_list.end() - 1))
        {
        }
        float x1;
        float x2;
    };

    virtual void printData() = 0;

    BaseBorder(bType) noexcept;

private:
    bType b_type;
};
} // namespace sml

#endif // !BASE_BORDER_HPP