#ifndef FORCES_HPP
#define FORCES_HPP

#include <SFML/System/Vector2.hpp>

namespace sml
{

namespace forces
{

struct Force
{
    float magnitude;
    sf::Vector2f acceleration;
};

Force
gravity(float mass);

Force
getForce(float mass, float acceleration, const sf::Vector2f& direction_v);

Force
getForce(float mass, float acceleration, float direction_r);

} // namespace forces

} // namespace sml
#endif // !FORCES_HPP