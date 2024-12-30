#ifndef GUI_HPP
#define GUI_HPP

#include <unordered_map>

#include "gui/gui_object.hpp"

namespace gui
{
using GUIObjectPtr = std::shared_ptr<gui::GUIObject>;

class GUI
{
public:
    void draw(std::unordered_map<int, gui::GUIObjectPtr>& gui_objects);
};
} // namespace gui

#endif // !GUI_HPP