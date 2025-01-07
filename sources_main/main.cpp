#include <SFML/Graphics.hpp>

#include <iostream>

#include "core/core.hpp"
#include "util/collision_functions.hpp"

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

int
main()
{
    // core::Core app;
    // app.run();

    std::vector<sf::Vector2f> left = {
        {2.8f, 3.21f},
        {5.2f, 4.4  },
        {7.2,  2.1f },
        {1.25, 0.5  }
    };
    left.emplace_back(left[0]);

    std::vector<sf::Vector2f> right = {
        {3,    5.1},
        {4.3,  2.3},
        {-0.8, 0.8},
        {-1.1, 6.1}
    };
    right.emplace_back(right[0]);

    sf::Vector2f left_direction = {-1, -2}, right_direction = {1, 0};

    printVector(left);

    /////////////////////////////////////////////

    sf::VertexArray v_arr_left  = createRect(left, sf::Color::Red);
    sf::VertexArray v_arr_right = createRect(right, sf::Color::Green);

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
                std::cout << "----- Allign -----\n";
                printVector(left);

                v_arr_left = createRect(left, sf::Color::Red);
            }
        }

        window.clear();
        window.draw(v_arr_left);
        window.draw(v_arr_right);
        window.display();
    }
}