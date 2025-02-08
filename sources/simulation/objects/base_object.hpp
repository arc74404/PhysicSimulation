#ifndef BASE_OBJECT_HPP
#define BASE_OBJECT_HPP

#include <SFML/System/Vector2.hpp>

#include <cstdarg>
#include <fstream>

#include "simulation/polygon/polygon.hpp"

#include "collision_context.hpp"
#include "mass.hpp"

namespace sml
{
using BaseBorderPtr = std::shared_ptr<sml::BaseBorder>;

using Point = sf::Vector2f;

class BaseObject;

using BaseObjectPtr = std::shared_ptr<BaseObject>;

class BaseObject : public Polygon
{
public:
    enum class FormType
    {
        NEW     = 0,
        PATTERN = 1
    };

    template <typename T>
    void saveData(std::ostream& os, BaseObjectPtr other, T& col_data);

    ///////////
    void setWeight(float w);

    explicit BaseObject(FormType upd_status) noexcept;

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

    void updateSpeed(const sf::Vector2f& normal);

    void updateSpeed(const sf::Vector2f& normal,
                     const sf::Vector2f& other_speed, float other_weight);

    CollisionContext m_collision_context;

    Point m_position;
    Bounds m_global_bounds;
    std::vector<Point> m_global_points;

    sf::Vector2f m_speed;

    Mass m_mass;

    FormType m_form_type;
};

template <typename T>
void
BaseObject::saveData(std::ostream& os, BaseObjectPtr other, T& col_data)
{
    for (auto& i : m_global_points)
    {
        os << "{" << i.x << ", " << i.y << "}," << '\n';
    }
    os << "---\n";
    for (auto& i : other->m_global_points)
    {
        os << "{" << i.x << ", " << i.y << "}," << '\n';
    }
    os << "---\n";
    os << col_data.allign_vector.x << " " << col_data.allign_vector.y << '\n';
    os << col_data.unit_normal.x << " " << col_data.unit_normal.y << '\n';
}

} // namespace sml
#endif // !BASE_OBJECT_HPP