#include <SFML/Graphics.hpp>

#include <iostream>

#include "core/core.hpp"
#include "util/collision_functions.hpp"

// #define DEBUGGING_GRAPHICS

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
        v_arr[i].position.x = vec[i].x * m + 200;
        v_arr[i].position.y = vec[i].y * m + 200;
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
        {3.6f,  1.28f },
        {2.34f, -0.67f},
        {1.89,  1.28f },
        {1.47,  2.24f },
        {5.36f, 2.76f }
    };
    left.emplace_back(left[0]);

    std::vector<sf::Vector2f> right = {
        {1.07308, 3.04178},
        {3.28594, 1.87554},
        {0.81594, 0.58257},
        {0.45757, 0.81028}
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

    // Start the game loop
    while (window.isOpen())
    {
        // Process events
        while (window.pollEvent(event))
        {
            // Close window: exit
            if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) window.close();
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                utl::allign(left, left_direction, right);
                // std::cout << "----- Allign -----\n";
                // printVector(left);

                v_arr_left = createRect(left, sf::Color::Red);
            }
        }

        window.clear();
        window.draw(v_arr_left);
        window.draw(v_arr_right);
        window.display();
    }
#endif
}