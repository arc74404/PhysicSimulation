#ifndef RECTANGLE_OBJECT_HPP
#define RECTANGLE_OBJECT_HPP

#include "pattern_object.hpp"

namespace sml
{
class RectangleObject : public PatternObject
{
public:
    RectangleObject();

    RectangleObject(const sf::Vector2f& size, const sf::Vector2f& position);

    void setSize(const sf::Vector2f& size);

private:
};
} // namespace sml
#endif // !RECTANGLE_OBJECT_HPP