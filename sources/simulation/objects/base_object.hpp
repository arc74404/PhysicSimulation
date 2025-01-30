#ifndef BASE_OBJECT_HPP
#define BASE_OBJECT_HPP

#include <SFML/System/Vector2.hpp>

#include <cstdarg>

#include "simulation/polygon/polygon.hpp"

#include "mass.hpp"

namespace sml
{
using BaseBorderPtr = std::shared_ptr<sml::BaseBorder>;

using Point = sf::Vector2f;

class BaseObject : public Polygon
{
public:
    enum class FormType
    {
        NEW     = 0,
        PATTERN = 1
    };

    explicit BaseObject(FormType upd_status) noexcept;

    void printGlobalBounds();

    bool handleCollision(std::shared_ptr<BaseObject> other,
                         bool is_right_const = false) noexcept;

    void updateSpecifications(float time) noexcept;

    const std::vector<Point>& getPoints() const noexcept;

protected:
    void deleteAllPoints() noexcept;

    virtual void setPosition(const Point& pos);

    void createObject();

    void updGlobalPointsAndBounds() noexcept;

private:
    void move(const sf::Vector2f& vec);

    void updateSpeed(const sf::Vector2f& normal,
                     const sf::Vector2f& other_speed, float other_weight);

    std::optional<sf::Vector2f> m_collision_normal;

    Point m_position;
    Bounds m_global_bounds;
    std::vector<Point> m_global_points;

    sf::Vector2f m_speed;

    Mass m_mass;

    FormType m_form_type;
};

using BaseObjectPtr = std::shared_ptr<BaseObject>;

} // namespace sml
#endif // !BASE_OBJECT_HPP