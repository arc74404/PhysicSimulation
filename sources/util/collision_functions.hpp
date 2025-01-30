#ifndef COLLISION_FUNCTIONS_HPP
#define COLLISION_FUNCTIONS_HPP

#include <SFML/System/Vector2.hpp>

#include <optional>
#include <vector>

namespace utl
{

using Point = sf::Vector2f;

using Section = std::pair<Point, Point>;

namespace CollisionHandler
{

struct CollisionData
{
    sf::Vector2f allign_vector;
    sf::Vector2f unit_normal;
};

std::optional<CollisionData>
getCollisionData(const std::vector<Point>& left,
                 const sf::Vector2f& left_direction,
                 const std::vector<Point>& right);

std::optional<Point>
getIntersection(const Section& left, const Section& right) noexcept;

std::optional<Point>
isIntersect(Section left, Section right);

Section
getDirectionalRay(const sf::Vector2f& direction, const Point& p);

Section
getCounterDirectionalRay(const sf::Vector2f& direction, const Point& p);

float
getDistance(const Point& p1, const Point& p2);

std::optional<CollisionData>
getCollisionData(const std::vector<Point>& first, const sf::Vector2f& direction,
                 const std::vector<Point>& second, bool is_counter_directional);

sf::Vector2f
getNormal(const Section& section);

sf::Vector2f
getReflectionVector(const sf::Vector2f& normal,
                    const sf::Vector2f& movement_vector);

float
getScalarProduct(const sf::Vector2f& vec1, const sf::Vector2f& vec2);

sf::Vector2f
normalize(const sf::Vector2f& vec) noexcept;

}; // namespace CollisionHandler

} // namespace utl

#endif // COLLISION_FUNCTIONS_HPP