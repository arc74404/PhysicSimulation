#include "circle_object.hpp"

#include "simulation/borders/circle_border.hpp"

sml::CircleObject::CircleObject() : CircleObject(0.f, {0, 0})
{
}

sml::CircleObject::CircleObject(float radius, const Point& centre)
    : PatternObject(PatternType::CIRCLE)
{
    setPosition({centre.x - radius, centre.y - radius});

    CircleBorder circle(radius);

    addBorder(std::make_unique<CircleBorder>(circle), true);
}