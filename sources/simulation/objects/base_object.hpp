#ifndef BASE_OBJECT_HPP
#define BASE_OBJECT_HPP

#include <SFML/Graphics.hpp>

#include <cstdarg>

#include "simulation/borders/base_border.hpp"

namespace sml
{
using BaseBorderPtr = std::unique_ptr<sml::BaseBorder>;

using Point = sf::Vector2f;
using Point = sf::Vector2f;

class BaseObject
{
public:
    enum class FormType
    {
        NEW     = 0,
        PATTERN = 1
    };

    BaseObject(FormType upd_status) noexcept;

    void printPoints() noexcept;

protected:
    bool addBorder(BaseBorderPtr&&);
    void fillPointVector();

private:
    float getRight();
    float getBottom();
    float getLeft();
    float getTop();

    void findMassCenter();

    void allign();

    Point m_position;

    Point m_mass_center;

    std::vector<Point> m_point_vector;

    std::vector<BaseBorderPtr> m_border_vector;

    FormType m_form_status;

    bool can_add_new_border;
};
} // namespace sml
#endif // !BASE_OBJECT_HPP