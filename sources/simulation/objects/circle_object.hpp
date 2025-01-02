#ifndef CIRCLE_OBJECT_HPP
#define CIRCLE_OBJECT_HPP

#include "pattern_object.hpp"

namespace sml
{
class CircleObject : public PatternObject
{
public:
    CircleObject();

    CircleObject(float radius, const Point& centre);

    void setRadius(float r);

    void setCentre(const sf::Vector2f& position);

private:
    Point m_centre;
    float m_radius;
};
} // namespace sml
#endif // !CIRCLE_OBJECT_HPP