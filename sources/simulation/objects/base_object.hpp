#ifndef BASE_OBJECT_HPP
#define BASE_OBJECT_HPP

#include <SFML/System/Vector2.hpp>

#include <cstdarg>

#include "simulation/borders/base_border.hpp"

#include "bounds.hpp"

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

    void printGlobalBounds();

    bool handleCollision(std::shared_ptr<BaseObject> other,
                         bool is_right_const = false) noexcept;

    void updateSpecifications(float time) noexcept;

    void updatePointsPosition();

    const std::vector<Point>& getPoints() const noexcept;

protected:
    void addBorder(const BaseBorderPtr& border, bool is_final_border = false);
    void addPoint(const Point& point, bool is_final_point = false);

    void deleteAllPoints() noexcept;

    virtual void setPosition(const Point& pos);

    void createObject();

private:
    Bounds getLocalBounds() const noexcept;
    Bounds getGlobalBounds() const noexcept;

    void move(const sf::Vector2f& vec);

    //////////
    void findGlobalBounds() noexcept;
    void findLocalBounds() noexcept;
    void findMassCenter();
    void findMass();
    void allignPoints();

    /////////
    void updateSpeed(const sf::Vector2f& normal, float k);

    float m_elasticity_coefficient;

    Bounds m_local_bounds;
    Bounds m_global_bounds;

    sf::Vector2f m_speed;

    Point m_position;

    float m_mass;

    Point m_mass_center;

    std::vector<Point> m_points;
    std::vector<Point> m_points_with_position;

    FormType m_form_type;
};

using BaseObjectPtr = std::shared_ptr<BaseObject>;

} // namespace sml
#endif // !BASE_OBJECT_HPP