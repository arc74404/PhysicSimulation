#include "rectangle_object.hpp"

#include "simulation/borders/def_scope.hpp"
#include "simulation/borders/linear_border.hpp"
#include "simulation/borders/x_const_border.hpp"
#include "simulation/borders/y_limit.hpp"

using DefScope = sml::DefScope;
using YLimit   = sml::YLimit;

void
sml::RectangleObject::setSize(const sf::Vector2f& size)
{
    addPoint({0, 0});
    addPoint({size.x, 0});
    addPoint({size.x, size.y});
    addPoint({0, size.y}, true);
}

sml::RectangleObject::RectangleObject() : RectangleObject({0, 0}, {0, 0})
{
}

sml::RectangleObject::RectangleObject(const sf::Vector2f& size,
                                      const sf::Vector2f& position)
    : PatternObject(PatternType::RECTANGLE)
{
    setSize(size);
    setPosition(position);
}