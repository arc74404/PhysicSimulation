#include "mass.hpp"

sml::Mass::Mass() : m_weight(0.f)
{
}

void
sml::Mass::findMassCentre(const std::vector<Point>& points,
                          const Bounds& bounds) // Monte carlo alg
{
    // for (float x; x < ; x += 0.3)
    // {
    //     for (float y; y < ; y += 0.3)
    //     {
    //     }
    // }
}

void
sml::Mass::setMassCentre(const sf::Vector2f& mc)
{
    m_mass_centre = mc;
}

void
sml::Mass::setWeight(float w)
{
    m_weight = std::abs(w);
}

float
sml::Mass::getWeight()
{
    return m_weight;
}