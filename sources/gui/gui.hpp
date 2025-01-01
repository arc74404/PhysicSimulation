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
    template <typename T> void draw(std::unordered_map<int, T>& gui_objects);
};
} // namespace gui

template <typename T>
void
gui::GUI::draw(std::unordered_map<int, T>& gui_objects)
{
    auto& window = gui::Window::getInstance();

    for (auto& go : gui_objects)
    {
        go.second.draw(window);
    }
}

#endif // !GUI_HPP