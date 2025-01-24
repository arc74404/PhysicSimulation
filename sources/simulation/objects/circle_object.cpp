#include "circle_object.hpp"

#include "simulation/borders/circle_border.hpp"

sml::CircleObject::CircleObject() : CircleObject(0.f, {0, 0})
{
}

sml::CircleObject::CircleObject(float radius, const Point& centre)
    : PatternObject(PatternType::CIRCLE)
{
    setRadius(radius);
    setCentre(centre);
}

void
sml::CircleObject::setRadius(float r)
{
    deleteAllPoints();

    m_radius = r;

    CircleBorder circle(r);

    addBorder(std::make_unique<CircleBorder>(circle), true, true);

    setPosition({m_centre.x - m_radius, m_centre.y - m_radius});
}

void
sml::CircleObject::setCentre(const sf::Vector2f& centre_position)
{
    m_centre = centre_position;
    setPosition({m_centre.x - m_radius, m_centre.y - m_radius});
}