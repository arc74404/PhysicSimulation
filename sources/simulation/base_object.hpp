#ifndef BASE_OBJECT_HPP
#define BASE_OBJECT_HPP

#include <SFML/Graphics.hpp>

#include <cstdarg>

#include "base_border.hpp"

namespace sml
{
using BaseBorderPtr = std::unique_ptr<sml::BaseBorder>;

using Point = sf::Vector2f;

class BaseObject
{
public:
    BaseObject() = default;

    enum class UpdStatus
    {
        UPDATABLE = 0,
        PERMANENT = 1
    };

    void printData() noexcept;

    bool addBorder(BaseBorderPtr&& b);

private:
    std::vector<Point> m_point_vector;

    std::vector<BaseBorderPtr> m_border_vector;

    UpdStatus m_upd_status;
};
} // namespace sml
#endif // !BASE_OBJECT_HPP