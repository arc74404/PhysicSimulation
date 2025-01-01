#include "figure.hpp"

gui::Figure::Figure() noexcept : GUIObject(Type::FIGURE)
{
    m_vertexes.setPrimitiveType(sf::PrimitiveType::LinesStrip);
}

void
gui::Figure::draw(Window& window) const
{
    window.draw(m_vertexes);
}

void
gui::Figure::updateVertexes(const std::vector<Point>& points)
{
    if (points.size() != m_vertexes.getVertexCount())
        m_vertexes.resize(points.size());

    auto s = m_vertexes.getVertexCount();

    for (int i = 0; i < s; ++i)
    {
        m_vertexes[i].position = points[i];
    }
}