#include <iostream>
#include <memory>

#include "simulation/base_object.hpp"
#include "simulation/linear_border.hpp"

using DefScope = sml::BaseBorder::DefScope;

int
main()
{
    // sf::RectangleShape shape({100, 100});

    // sf::RenderWindow window(sf::VideoMode(800, 600), "SFML window");

    // window.setFramerateLimit(60);

    // while (window.isOpen())
    // {
    //     window.draw(shape);
    //     window.display();
    //     window.clear();

    //     sf::Event event;
    //     while (window.pollEvent(event))
    //     {
    //         if (event.type == sf::Event::Closed) window.close();
    //     }
    // }

    sml::BaseObject bObj;
    // bObj.addBorders({lb3, lb2, lb});

    BaseBorderPtr border_ptr =
        std::make_unique<sml::LinearBorder>(DefScope{10, 10}, 3, 2);

    BaseBorderPtr border_ptr2 =
        std::make_unique<sml::LinearBorder>(DefScope{15, 15}, 1, 2);

    bObj.addBorders(border_ptr, border_ptr2);

    bObj.printData();

    std::cout << "End\n";
}