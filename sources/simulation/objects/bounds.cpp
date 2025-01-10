#include "bounds.hpp"

#include <SFML/Graphics/Rect.hpp>

void
sml::Bounds::move(const sf::Vector2f& move_vec)
{
    move(move_vec.x, move_vec.y);
}
void
sml::Bounds::move(float mx, float my)
{
    left += mx;
    right += mx;
    top += my;
    bottom += my;
}
bool
sml::Bounds::intersects(const Bounds& other)
{
    if (this->right < other.left || other.right < this->left ||
        this->top < other.bottom || other.top < this->bottom)
    {
        return false; // Нет пересечения
    }
    return true; // Есть пересечение
}