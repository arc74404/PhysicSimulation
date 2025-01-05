#ifndef COLLISION_FUNCTIONS_HPP
#define COLLISION_FUNCTIONS_HPP

#include <SFML/System/Vector2.hpp>

#include <optional>
#include <vector>

namespace utl
{
using Point = sf::Vector2f;

using Section = std::pair<Point, Point>;

void
allign(std::vector<Point>& left, const sf::Vector2f& left_direction,
       std::vector<Point>& right, const sf::Vector2f& right_direction);

std::optional<Point>
getIntersection(const Section& left, const Section& right) noexcept;

std::optional<Point>
isIntersect(Section left, Section right);

Section
getParallelSection(const sf::Vector2f& vector, const Point& p);

} // namespace utl

#endif // COLLISION_FUNCTIONS_HPP