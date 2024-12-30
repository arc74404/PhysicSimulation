#include "figure.hpp"

void
gui::Figure::draw(Window& window) const
{
    window.draw(m_vertexes);
}

void
gui::Figure::resize(std::size_t s)
{
    m_vertexes.resize(s);
}

void
gui::Figure::updateVertexes(const std::vector<Point>& points)
{
    auto s = m_vertexes.getVertexCount();

    for (int i = 0; i < s; ++i)
    {
        m_vertexes[i].position = points[i];
    }
}