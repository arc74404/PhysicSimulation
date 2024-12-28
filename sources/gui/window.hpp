#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <SFML/Graphics.hpp>

// #include "event/gui_event.hpp"

namespace gui
{
class Window
{
public:
    static Window& getInstance();

    void draw(sf::VertexArray& vertex_array);

    void close();

    void clear();
    void display();

    sf::Event getEvent();

private:
    Window();

    sf::RenderWindow m_window;

    sf::Event m_event;
};
} // namespace gui

#endif // WINDOW_HPP