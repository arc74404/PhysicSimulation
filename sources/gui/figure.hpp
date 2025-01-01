#ifndef FIGURE_HPP
#define FIGURE_HPP

#include "gui/gui_object.hpp"

using Point = sf::Vector2f;

namespace gui
{

class Figure : public GUIObject
{
public:
    Figure() noexcept;

    void draw(Window& window) const override;

    void updateVertexes(const std::vector<Point>& points);

private:
    sf::VertexArray m_vertexes;
};
} // namespace gui

#endif // FIGURE_HPP