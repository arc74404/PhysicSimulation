#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <SFML/Graphics.hpp>

namespace gui
{
class Window
{
public:
    static Window& getInstance();

    void draw(sf::VertexArray& vertex_array);

private:
    Window() = default;

    sf::RenderWindow m_window;
};
} // namespace gui

#endif // WINDOW_HPP