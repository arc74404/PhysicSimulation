#ifndef CIRCLE_OBJECT_HPP
#define CIRCLE_OBJECT_HPP

#include "pattern_object.hpp"

namespace sml
{
class CircleObject : public PatternObject
{
public:
    CircleObject();

    CircleObject(float radius);

    void setRadius(float radius);

private:
};
} // namespace sml
#endif // !CIRCLE_OBJECT_HPP