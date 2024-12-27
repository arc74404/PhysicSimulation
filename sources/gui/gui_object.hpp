#ifndef GUI_OBJECT_HPP
#define GUI_OBJECT_HPP

#include <SFML/Graphics.hpp>

#include "window.hpp"

namespace gui
{

using Point = sf::Vector2f;

class GUIObject
{
public:
    GUIObject() = default;

    void draw(Window& window);

    void setVertexes(std::vector<Point> points);

private:
    sf::VertexArray m_vertexes;
};
} // namespace gui

#endif // GUI_OBJECT_HPP