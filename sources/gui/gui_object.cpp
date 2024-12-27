#include "gui_object.hpp"

#include "window.hpp"

void
gui::GUIObject::draw(Window& window)
{
    window.draw(m_vertexes);
}

void
gui::GUIObject::setVertexes(std::vector<Point> points)
{
    auto points_count = points.size();
    m_vertexes.resize(points_count);

    for (int i = 0; i < points_count; ++i)
    {
        m_vertexes[i].position = points[i];
        m_vertexes[i].color    = sf::Color(sf::Color::White);
    }
}