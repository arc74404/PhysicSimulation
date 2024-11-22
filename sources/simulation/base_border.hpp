#ifndef BASE_BORDER_HPP
#define BASE_BORDER_HPP

#include <SFML/Graphics.hpp>

#include <initializer_list>
#include <mutex>

namespace sml
{

using Point = sf::Vector2f;

class BaseBorder
{
public:
    enum class bType
    {
        LINEAR  = 0,
        X_CONST = 1
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
    // struct Coordinate
    // {
    //     float x;
    //     float y;
    // };

    virtual void printData() const = 0;

    BaseBorder(bType, DefScope = {0, 0}) noexcept;

    bool canConnect(std::unique_ptr<BaseBorder>& other_border_ptr,
                    ConnectionWay con_way) const;

    constexpr bType getType() const noexcept;

    Point getEndPoint() const;

    Point getBeginPoint() const;

    DefScope getDefScope() const noexcept;

    virtual float getOrdinate(float x) const noexcept = 0;

private:
    DefScope m_function_definition_scope;

    bType b_type;
};
} // namespace sml

#endif // !BASE_BORDER_HPP