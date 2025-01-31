#include "base_object.hpp"

#include <iomanip>
#include <iostream>

#include "core/variable_storage.hpp"
#include "simulation/borders/base_equation_border.hpp"
#include "simulation/simulation/forces.hpp"
#include "util/collision_functions.hpp"
#include "util/extra_math_functions.hpp"

sml::BaseObject::BaseObject(FormType form_status) noexcept
    : m_form_type(form_status), m_speed(0, 0)
{
    m_mass.setWeight(100);
}

void
sml::BaseObject::setWeight(float w)
{
    m_mass.setWeight(w);
}

void
sml::BaseObject::deleteAllPoints() noexcept
{
    Polygon::clear();
    m_global_points.clear();
    m_global_bounds.update(m_global_points);
}

void
sml::BaseObject::updGlobalPointsAndBounds() noexcept
{
    Polygon::copyWithOffset(m_global_points, m_global_bounds, m_position);
}

void
sml::BaseObject::createObject()
{
    updGlobalPointsAndBounds();
}

void
sml::BaseObject::move(const sf::Vector2f& vec)
{
    m_position += vec;

    m_global_bounds.move(vec);

    updGlobalPointsAndBounds();
}

void
sml::BaseObject::setPosition(const Point& pos)
{
    m_position = pos;

    updGlobalPointsAndBounds();
}

void
sml::BaseObject::updateSpecifications(float time) noexcept
{
    auto gravity_force = sml::forces::gravity(m_mass.getWeight());

    sf::Vector2f result_force = gravity_force.acceleration;

    if (m_collision_unit_normal.has_value())
    {
        result_force +=
            sml::forces::counteraction(gravity_force, m_mass.getWeight(),
                                       m_collision_unit_normal.value())
                .acceleration;

        m_collision_unit_normal.reset();
    }

    int pixels_per_metr =
        core::VariableStorage::getInstance().getInt("pixels_per_metr");

    m_speed += (result_force * time * float(pixels_per_metr));

    move({m_speed.x * time, m_speed.y * time});
}

void
sml::BaseObject::printGlobalBounds()
{
    std::cout << "--------------------\n";
    std::cout << "Left: " << m_global_bounds.left << '\n';
    std::cout << "Right: " << m_global_bounds.right << '\n';
    std::cout << "Top: " << m_global_bounds.top << '\n';
    std::cout << "Bottom: " << m_global_bounds.bottom << '\n';
    std::cout << "--------------------\n";
}

void
sml::BaseObject::updateSpeed(const sf::Vector2f& normal)
{
    auto impulse_direction =
        utl::CollisionHandler::getReflectionVector(normal, m_speed);

    this->m_speed =
        impulse_direction * utl::getLength(this->m_speed) *
        core::VariableStorage::getInstance().getFloat("elasticity_coefficient");
}

void
sml::BaseObject::updateSpeed(const sf::Vector2f& normal,
                             const sf::Vector2f& other_speed,
                             float other_weight)
{
    // std::vector<double> v1_minus_v2 = subtractVectors(v1, v2);
    sf::Vector2f v1_minus_v2 = this->m_speed - other_speed;

    // ((v1 - v2) . n)
    double dot_product_v1_minus_v2_n =
        utl::CollisionHandler::getScalarProduct(v1_minus_v2, normal);

    // 2 * m2 / (m1 + m2)
    double scalar_factor =
        (2.f * other_weight) / (this->m_mass.getWeight() + other_weight);

    // (2 * m2 / (m1 + m2)) * ((v1 - v2) . n)
    double scalar_term = scalar_factor * dot_product_v1_minus_v2_n;

    // ((2 * m2 / (m1 + m2)) * ((v1 - v2) . n) ) * n
    sf::Vector2f vector_term = {normal.x * float(scalar_term),
                                normal.y * float(scalar_term)};

    // u1 = v1 - ((2 * m2 / (m1 + m2)) * (v1 - v2) . n ) * n
    this->m_speed = this->m_speed - vector_term;
}

bool
sml::BaseObject::handleCollision(std::shared_ptr<BaseObject> other,
                                 bool is_right_const) noexcept
{
    bool was_collision = false;

    if (this->m_global_bounds.intersects(other->m_global_bounds))
    {

        auto collision_data = utl::CollisionHandler::getCollisionData(
            this->m_global_points, this->m_speed, other->m_global_points);

        if (collision_data.has_value())
        {
            m_collision_unit_normal.emplace(collision_data->unit_normal);

            move(collision_data->allign_vector);
            was_collision = true;

            if (is_right_const)
            {
                updateSpeed(collision_data->unit_normal);
            }
            else
            {
                updateSpeed(collision_data->unit_normal, other->m_speed,
                            other->m_mass.getWeight());
                other->updateSpeed(-collision_data->unit_normal, this->m_speed,
                                   this->m_mass.getWeight());
            }
        }
    }

    return was_collision;
}

const std::vector<sml::Point>&
sml::BaseObject::getPoints() const noexcept
{
    return m_global_points;
}