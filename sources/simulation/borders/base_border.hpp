#ifndef BASE_BORDER_HPP
#define BASE_BORDER_HPP

#include <SFML/Graphics.hpp>

#include <initializer_list>
#include <mutex>
#include <optional>

#include "section.hpp"

namespace sml
{

using Point = sf::Vector2f;

class BaseBorder
{
public:
    enum class BaseType
    {
        FUNCTION = 0, // y = kx + b
        EQUATION = 1  // x = 5
    };
    enum class ConnectionWay
    {
        END_TO_END   = 0,
        END_TO_BEGIN = 1,
        BEGIN_TO_END,
        BEGIN_TO_BEGIN,
        NO_WAY
    };

    // virtual void printData() const = 0;

    BaseBorder(BaseType) noexcept;

    virtual std::vector<Point> getPoints() const = 0;

    BaseType getBaseType() const noexcept;

    virtual Point getEndPoint() const noexcept = 0;

    virtual Point getBeginPoint() const noexcept = 0;

private:
    BaseType b_type;
};

using BaseBorderPtr = std::shared_ptr<BaseBorder>;

} // namespace sml

#endif // !BASE_BORDER_HPP