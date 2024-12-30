#ifndef BASE_OBJECT_HPP
#define BASE_OBJECT_HPP

#include <SFML/Graphics.hpp>

#include <cstdarg>

#include "simulation/borders/base_border.hpp"

namespace sml
{
using BaseBorderPtr = std::unique_ptr<sml::BaseBorder>;

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

    void update() noexcept;

    const std::vector<Point>& getPoints() const noexcept;

protected:
    void addBorder(const BaseBorderPtr& border, bool is_final_border = false);
    void addPoint(const Point& point, bool is_final_point = false);

private:
    float getRight() const;
    float getBottom() const;
    float getLeft() const;
    float getTop() const;

    void findMassCenter() const;

    void allign();

    Point m_position;

    Point m_mass_center;

    std::vector<Point> m_points;

    FormType m_form_type;
};
} // namespace sml
#endif // !BASE_OBJECT_HPP