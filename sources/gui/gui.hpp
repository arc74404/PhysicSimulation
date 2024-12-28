#ifndef GUI_HPP
#define GUI_HPP

#include <vector>

#include "gui/gui_object.hpp"

namespace gui
{
using GUIObjectPtr = std::unique_ptr<gui::GUIObject>;

class GUI
{
public:
    void draw(std::vector<GUIObjectPtr>& gui_objects);
};
} // namespace gui

#endif // !GUI_HPP