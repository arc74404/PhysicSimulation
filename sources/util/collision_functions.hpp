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
allign(std::vector<Point>& left, std::vector<Point>& right);

std::optional<Point>
getIntersection(const Section& left, const Section& right) noexcept;

} // namespace utl

#endif // COLLISION_FUNCTIONS_HPP