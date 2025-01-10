#ifndef BOUNDS_HPP
#define BOUNDS_HPP

#include <SFML/System/Vector2.hpp>

namespace sml
{

struct Bounds
{
    float left;
    float right;
    float top;
    float bottom;

    void move(const sf::Vector2f& move_vec);

    void move(float mx, float my);

    bool intersects(const Bounds& other);
};
} // namespace sml

#endif // BOUNDS_HPP