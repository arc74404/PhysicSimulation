#include "circle_object.hpp"

sml::CircleObject::CircleObject() : CircleObject(0.f)
{
}

sml::CircleObject::CircleObject(float radius) : CircleObject(0.f)
{
}

void
sml::CircleObject::setRadius(float radius)
{

	// addBorder();
    fillPointVector();
}