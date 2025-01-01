#include "gui_object.hpp"

gui::GUIObject::GUIObject(Type t) noexcept : m_type(t)
{
}

gui::GUIObject::Type
gui::GUIObject::getType() noexcept
{
    return m_type;
}