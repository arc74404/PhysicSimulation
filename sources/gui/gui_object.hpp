#ifndef GUI_OBJECT_HPP
#define GUI_OBJECT_HPP

#include "window.hpp"

namespace gui
{
class GUIObject
{
public:
    virtual void draw(Window& window) const = 0;

private:
};
} // namespace gui

#endif // GUI_OBJECT_HPP