#include "window.hpp"

#include <iostream>
gui::Window::Window()
{
    m_window.create(sf::VideoMode({800, 600}), "Simulation");

    m_view.setCenter(400, 300);
    m_view.setSize(m_window.getSize().x, m_window.getSize().y);

    m_view.zoom(2);

    m_window.setView(m_view);
}

void
gui::Window::draw(const sf::VertexArray& vertex_array)
{
    m_window.draw(vertex_array);
}

gui::Window&
gui::Window::getInstance()
{
    static Window w;
    return w;
}

sf::Event::EventType
gui::Window::getEvent()
{
    m_window.pollEvent(m_event);

    return m_event.type;
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