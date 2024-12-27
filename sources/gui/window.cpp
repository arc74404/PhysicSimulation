#include "window.hpp"

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