#include "bounds.hpp"

#include <SFML/Graphics/Rect.hpp>

sml::Bounds::Bounds() noexcept : left(0.f), right(0.f), top(0.f), bottom(0.f)
{
}

void
sml::Bounds::update(const std::vector<Point>& points) noexcept
{
    if (!points.size())
    {
        left   = 0;
        right  = 0;
        bottom = 0;
        top    = 0;
        return;
    }
    left = std::min_element(points.begin(), points.end(),
                            [](const Point& a, const Point& b) noexcept
                            { return a.x < b.x; })
               ->x;
    right = std::max_element(points.begin(), points.end(),
                             [](const Point& a, const Point& b) noexcept
                             { return a.x < b.x; })
                ->x;
    top = std::max_element(points.begin(), points.end(),
                           [](const Point& a, const Point& b) noexcept
                           { return a.y < b.y; })
              ->y;
    bottom = std::min_element(points.begin(), points.end(),
                              [](const Point& a, const Point& b) noexcept
                              { return a.y < b.y; })
                 ->y;
}

void
sml::Bounds::move(const sf::Vector2f& move_vec) noexcept
{
    move(move_vec.x, move_vec.y);
}
void
sml::Bounds::move(float mx, float my) noexcept
{
    left += mx;
    right += mx;
    top += my;
    bottom += my;
}

bool
sml::Bounds::intersects(const Bounds& other) const noexcept
{
    if (this->right < other.left || other.right < this->left ||
        this->top < other.bottom || other.top < this->bottom)
    {
        return false; // Нет пересечения
    }
    return true; // Есть пересечение
}