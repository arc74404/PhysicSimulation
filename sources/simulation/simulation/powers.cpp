#include "powers.hpp"

#include "core/variable_storage.hpp"

sml::forces::Force
sml::forces::gravity(float mass)
{
    Force res;
    float g = core::VariableStorage::getInstance().getFloat(
        "acceleration_of_gravity");

    res.magnitude      = mass * g;
    res.acceleration.x = 0;
    res.acceleration.y = g;
    return res;
}

sml::forces::Force
sml::forces::getForce(float mass, float acceleration,
                      const sf::Vector2f& direction_v)
{
    Force res;
    return res;
}

sml::forces::Force
sml::forces::getForce(float mass, float acceleration, float direction_r)
{
    Force res;
    return res;
}