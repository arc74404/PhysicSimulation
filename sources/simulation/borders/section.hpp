#ifndef SECTION_HPP
#define SECTION_HPP

#include <SFML/Graphics.hpp>

namespace sml
{

using Point = sf::Vector2f;

struct Section
{

    Section();
    
    Section(const Point& p1, const Point& p2);

    Point begin;
    Point end;
};
} // namespace sml

#endif // !SECTION_HPP