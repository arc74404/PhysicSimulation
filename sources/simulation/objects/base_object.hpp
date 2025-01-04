#ifndef BASE_OBJECT_HPP
#define BASE_OBJECT_HPP

#include <SFML/System/Vector2.hpp>

#include <cstdarg>

#include "simulation/borders/base_border.hpp"

namespace sml
{
using BaseBorderPtr = std::shared_ptr<sml::BaseBorder>;

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

    static void handleCollision(std::shared_ptr<BaseObject> left,
                                std::shared_ptr<BaseObject> right,
                                bool is_right_const = false) noexcept;

    void update(float time) noexcept;

    const std::vector<Point>& getPoints() const noexcept;

protected:
    void addBorder(const BaseBorderPtr& border, bool is_final_border = false);
    void addPoint(const Point& point, bool is_final_point = false);

    void deleteAllPoints() noexcept;

    virtual void setPosition(const Point& pos);

private:
    float getRight() const noexcept;
    float getBottom() const noexcept;
    float getLeft() const noexcept;
    float getTop() const noexcept;

    void findMassCenter();
    void findMass();

    void allign();

    sf::Vector2f m_speed;

    Point m_position;

    float m_mass;

    Point m_mass_center;

    std::vector<Point> m_points;
    std::vector<Point> m_points_with_position;

    FormType m_form_type;
};
} // namespace sml
#endif // !BASE_OBJECT_HPP