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
    sf::Vector2f s = {std::abs(size.x), std::abs(size.y)};

    XisConstBorder left(0, YLimit(0.f, s.y));
    BaseBorderPtr left_border = std::make_unique<XisConstBorder>(left);

    LinearBorder top(DefScope(0.f, s.x), 0.f, s.y);
    BaseBorderPtr top_border = std::make_unique<LinearBorder>(top);

    XisConstBorder right(s.x, YLimit(0.f, s.y));
    BaseBorderPtr right_border = std::make_unique<XisConstBorder>(right);

    LinearBorder bottom(DefScope(0.f, s.x));
    BaseBorderPtr bottom_border = std::make_unique<LinearBorder>(bottom);

    addBorder(std::move(left_border));
    addBorder(std::move(top_border));
    addBorder(std::move(right_border));
    addBorder(std::move(bottom_border), true);
}

sml::RectangleObject::RectangleObject() : RectangleObject({0, 0})
{
}

sml::RectangleObject::RectangleObject(const sf::Vector2f& size)
    : PatternObject(PatternType::RECTANGLE)
{
    setSize(size);
}