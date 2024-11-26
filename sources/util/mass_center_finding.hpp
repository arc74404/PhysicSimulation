#ifndef MASS_CENTER_FINDING_HPP
#define MASS_CENTER_FINDING_HPP

#include <SFML/Graphics.hpp>

namespace utl
{

using Point = sf::Vector2f;

bool
isPointInPolygon(const Point& p, const std::vector<Point>& polygon);
} // namespace utl

#endif // !MASS_CENTER_FINDING_HPP