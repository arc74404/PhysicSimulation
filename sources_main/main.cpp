#include <SFML/Graphics.hpp>

#include <iostream>

#include "core/core.hpp"
#include "util/collision_functions.hpp"

#define DEBUGGING_GRAPHICS

#ifdef DEBUGGING_GRAPHICS

void
printVector(std::vector<sf::Vector2f>& vec)
{
    std::cout << "----------------\n";
    std::cout << "  x" << "\t" << "  y" << '\n';
    std::cout << "----------------\n";
    for (int i = 0; i < vec.size(); ++i)
    {
        std::cout << vec[i].x << " \t" << vec[i].y << '\n';
    }
}

sf::VertexArray
createRect(const std::vector<sf::Vector2f>& vec, sf::Color color)
{
    sf::VertexArray v_arr(sf::PrimitiveType::LinesStrip);

    v_arr.resize(vec.size());
    float m = 30;
    for (int i = 0; i < vec.size(); ++i)
    {
        v_arr[i].position.x = vec[i].x;
        v_arr[i].position.y = vec[i].y;
        v_arr[i].color      = color;
    }
    return v_arr;
}
#endif

int
main()
{
#ifndef DEBUGGING_GRAPHICS
    core::Core app;
    app.run();
#else
    std::vector<sf::Vector2f> left = {
        {100, 430.961},
        {170, 430.961},
        {170, 500.961},
        {100, 500.961},
        {100, 430.961}
    };
    left.emplace_back(left[0]);

    std::vector<sf::Vector2f> right = {
        {0,   500},
        {500, 500},
        {500, 600},
        {0,   600},
        {0,   500}
    };
    right.emplace_back(right[0]);

    sf::Vector2f left_direction = {-1, -2}, right_direction = {1, 0};

    // printVector(left);

    /////////////////////////////////////////////

    sf::VertexArray v_arr_left  = createRect(left, sf::Color::White);
    sf::VertexArray v_arr_right = createRect(right, sf::Color::White);

    v_arr_left[2].color = sf::Color::Red;
    v_arr_left[3].color = sf::Color::Red;
    v_arr_left[4].color = sf::Color::Green;

    v_arr_right[1].color = sf::Color::Magenta;
    v_arr_right[2].color = sf::Color::Yellow;

    sf::RenderWindow window(sf::VideoMode({800, 600}), "SFML window");

    sf::Event event;

    sf::View m_view;

    m_view.setCenter(400, 300);
    m_view.setSize(window.getSize().x, window.getSize().y);

    m_view.zoom(2);

    window.setView(m_view);

    window.setFramerateLimit(80);

    // Start the game loop
    while (window.isOpen())
    {
        // Process events
        while (window.pollEvent(event))
        {
            // Close window: exit
            if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) window.close();
        }

        window.clear();
        window.draw(v_arr_left);
        window.draw(v_arr_right);
        window.display();
    }
#endif
}