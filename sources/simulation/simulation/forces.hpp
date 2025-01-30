#ifndef FORCES_HPP
#define FORCES_HPP

#include <SFML/System/Vector2.hpp>

namespace sml
{

namespace forces
{

struct Force
{
    Force();
    float magnitude;
    sf::Vector2f acceleration;
};

Force
gravity(float mass) noexcept;

Force
counteraction(const Force& grav, float weight, const sf::Vector2f& normal) noexcept;

} // namespace forces

} // namespace sml
#endif // !FORCES_HPP