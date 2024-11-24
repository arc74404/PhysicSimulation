#ifndef BASE_FUNCTION_BORDER_HPP
#define BASE_FUNCTION_BORDER_HPP

#include <SFML/Graphics.hpp>

#include "base_border.hpp"

namespace sml
{
using Point = sf::Vector2f;

class BaseFunctionBorder : public BaseBorder
{
public:
    enum class FunctionType
    {
        LINEAR = 0
    };

    enum class ConnectionWay
    {
        END_TO_END   = 0,
        END_TO_BEGIN = 1,
        BEGIN_TO_END,
        BEGIN_TO_BEGIN
    };

    struct DefScope
    {
        template <typename T>
        constexpr DefScope(T xx1, T xx2) noexcept
            : x1(static_cast<float>(xx1)), x2(static_cast<float>(xx2))
        {
        }
        template <typename T>
        constexpr DefScope(std::initializer_list<T> init_list) noexcept
            : x1(static_cast<float>(*init_list.begin())),
              x2(static_cast<float>(*(init_list.end() - 1)))
        {
        }
        float x1;
        float x2;
    };

    virtual void printData() const = 0;

    BaseFunctionBorder(FunctionType, DefScope = {0, 0}) noexcept;

    constexpr FunctionType getFunctionType() const noexcept;

    Point getEndPoint() const noexcept;

    Point getBeginPoint() const noexcept;

    DefScope getDefScope() const noexcept;

    virtual float getOrdinate(float x) const noexcept = 0;

private:
    DefScope m_function_definition_scope;

    FunctionType m_function_type;
};
} // namespace sml

#endif // BASE_FUNCTION_BORDER_HPP