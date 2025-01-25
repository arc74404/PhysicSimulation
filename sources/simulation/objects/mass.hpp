#ifndef MASS_HPP
#define MASS_HPP

#include <vector>

#include "SFML/System/Vector2.hpp"
#include "simulation/polygon/bounds.hpp"

namespace sml
{

using Point = sf::Vector2f;

class Mass
{
public:
    Mass();

    void setMassCentre(const sf::Vector2f& mc);

    void setWeight(float w);

    float getWeight();

    void findMassCentre(const std::vector<Point>& points, const Bounds& bounds);

private:
    float m_weight;

    sf::Vector2f m_mass_centre;
};
}; // namespace sml

#endif // MASS_HPP