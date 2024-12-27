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

private:
};
} // namespace sml
#endif // !CIRCLE_OBJECT_HPP