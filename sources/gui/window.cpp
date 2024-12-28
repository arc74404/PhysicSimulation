#include "window.hpp"

gui::Window::Window()
{
    m_window.create(sf::VideoMode({800, 600}), "Simulation");
}

void
gui::Window::draw(sf::VertexArray& vertex_array)
{
    m_window.draw(vertex_array);
}

gui::Window&
gui::Window::getInstance()
{
    static Window w;
    return w;
}

sf::Event
gui::Window::getEvent()
{
    m_window.pollEvent(m_event);

    return m_event;
}
void
gui::Window::close()
{
    m_window.close();
}

void
gui::Window::clear()
{
    m_window.clear();
}

void
gui::Window::display()
{
    m_window.display();
}