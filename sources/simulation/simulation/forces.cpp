#include "forces.hpp"

#include "core/variable_storage.hpp"
#include "util/collision_functions.hpp"

sml::forces::Force::Force() : magnitude(0.f)
{
}

sml::forces::Force
sml::forces::gravity(float weight) noexcept
{
    Force res;
    float g = core::VariableStorage::getInstance().getFloat(
        "acceleration_of_gravity");

    res.magnitude      = weight * g;
    res.acceleration.x = 0;
    res.acceleration.y = g;
    return res;
}

sml::forces::Force
sml::forces::counteraction(const Force& grav, float weight,
                           const sf::Vector2f& normal) noexcept
{
    Force res;

    res.magnitude = grav.magnitude;

    sf::Vector2f normalize_normal = utl::CollisionHandler::normalize(normal);

    if (normalize_normal.y < 0)
    {
        res.acceleration = normalize_normal * res.magnitude / weight;
    }
    else
    {
        res.acceleration = normalize_normal * res.magnitude * -1.f / weight;
    }
    return res;
}