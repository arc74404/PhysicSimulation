#ifndef BOUNDS_HPP
#define BOUNDS_HPP

#include <SFML/System/Vector2.hpp>

#include <vector>

namespace sml
{

using Point = sf::Vector2f;

struct Bounds
{
    float left;
    float right;
    float top;
    float bottom;

    Bounds() noexcept;

    void update(const std::vector<Point>& points) noexcept;

    void move(const sf::Vector2f& move_vec) noexcept;

    void move(float mx, float my) noexcept;

    bool intersects(const Bounds& other) const noexcept;
};
} // namespace sml

#endif // BOUNDS_HPP