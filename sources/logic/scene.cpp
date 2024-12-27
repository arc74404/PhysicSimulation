#include "scene.hpp"

#include "gui/window.hpp"

void
lgc::Scene::draw()
{
    auto& window = gui::Window::getInstance();

    for (auto& obj : m_gui_objects)
    {
        obj.draw(window);
    }
}

void
lgc::Scene::interact()
{
    for (auto& obj : m_gui_objects)
    {
        obj.interact(window);
    }
}