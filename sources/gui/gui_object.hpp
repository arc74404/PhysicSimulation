#ifndef GUI_OBJECT_HPP
#define GUI_OBJECT_HPP

#include "window.hpp"

namespace gui
{
class GUIObject
{
public:
    enum class Type
    {
        FIGURE = 0
    };

    GUIObject(Type t) noexcept;

    Type getType() noexcept;

    virtual void draw(Window& window) const = 0;

private:
    Type m_type;
};
} // namespace gui

#endif // GUI_OBJECT_HPP