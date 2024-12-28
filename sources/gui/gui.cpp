#include "gui.hpp"

void
gui::GUI::draw(std::vector<GUIObjectPtr>& gui_objects)
{
    auto& window = gui::Window::getInstance();

    window.clear();

    for (auto& go : gui_objects)
    {
        go->draw(window);
    }
    window.display();
}