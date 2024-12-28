#ifndef GUI_OBJECT_HPP
#define GUI_OBJECT_HPP

#include "window.hpp"

namespace gui
{
using Point = sf::Vector2f;

class GUIObject
{
public:
    virtual void draw(Window& window) = 0;

private:
};
} // namespace gui

#endif // GUI_OBJECT_HPP