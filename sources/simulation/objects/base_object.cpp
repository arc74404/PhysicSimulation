#include "base_object.hpp"

#include <iomanip>
#include <iostream>

#include "core/variable_storage.hpp"
#include "simulation/borders/base_equation_border.hpp"
#include "simulation/simulation/powers.hpp"
#include "util/collision_functions.hpp"
#include "util/extra_math_functions.hpp"

sml::BaseObject::BaseObject(FormType form_status) noexcept
    : m_form_type(form_status), m_speed(0, 0), m_elasticity_coefficient(0.5)
{
}

void
sml::BaseObject::findMassCenter()
{
}

void
sml::BaseObject::findMass()
{
    m_mass = 100.f;
    // if (m_is_const)
    // {
    //     m_mass = std::numeric_limits<float>::max();
    // }
}

void
sml::BaseObject::deleteAllPoints() noexcept
{
    PointsStorage::clear();
    m_global_points.clear();
    m_global_bounds.update(m_global_points);
}

// sml::Bounds
// sml::BaseObject::getLocalBounds() const noexcept
// {
//     return m_local_bounds;
// }

sml::Bounds
sml::BaseObject::getGlobalBounds() const noexcept
{
    return m_global_bounds;
}

void
sml::BaseObject::updGlobalBounds() noexcept
{
    PointsStorage::copyWithOffset(m_global_points, m_position);
}

// void
// sml::BaseObject::allignPoints()
// {
//     findLocalBounds();
//     float x_shift = getLocalBounds().left;
//     float y_shift = getLocalBounds().bottom;

//     m_local_bounds.move(-x_shift, -y_shift);

//     for (auto& p : m_points)
//     {
//         p.x -= x_shift;
//         p.y -= y_shift;
//     }
// }

void
sml::BaseObject::createObject()
{
    allignPoints();
    findGlobalBounds();
    findMassCenter();
    findMass();
}

// void
// sml::BaseObject::updatePointsPosition()
// {
//     for (int i = 0; i < m_points_with_position.size(); ++i)
//     {
//         m_points_with_position[i] = m_points[i] + m_position;
//     }
// }

void
sml::BaseObject::move(const sf::Vector2f& vec)
{
    m_position += vec;

    m_global_bounds.move(vec);

    updatePointsPosition();
}

void
sml::BaseObject::setPosition(const Point& pos)
{
    m_position = pos;

    findGlobalBounds();
    updatePointsPosition();
}

void
sml::BaseObject::updateSpecifications(float time) noexcept
{
    auto f = sml::forces::gravity(m_mass);

    int pixels_per_metr =
        core::VariableStorage::getInstance().getInt("pixels_per_metr");

    m_speed.x += (f.acceleration.x * time * pixels_per_metr);
    m_speed.y += (f.acceleration.y * time * pixels_per_metr);

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
sml::BaseObject::updateSpeed(const sf::Vector2f& normal, float k)
{
    auto impulse_direction =
        utl::CollisionHandler::getReflectionVector(normal, m_speed);

    float this_speed_module = utl::getLength(this->m_speed);

    this->m_speed = impulse_direction * this_speed_module * k;
}

bool
sml::BaseObject::handleCollision(std::shared_ptr<BaseObject> other,
                                 bool is_right_const) noexcept
{
    bool was_collision = false;

    if (this->m_global_bounds.intersects(other->m_global_bounds))
    {
        auto collision_data = utl::CollisionHandler::getCollisionData(
            this->m_points_with_position, this->m_speed,
            other->m_points_with_position);

        if (collision_data.has_value())
        {
            move(collision_data->allign_vector);
            was_collision = true;

            updateSpeed(collision_data->normal, 0.5);

            if (!is_right_const)
            {
                other->updateSpeed(collision_data->normal, 50.f);
            }
        }
    }

    return was_collision;
}

const std::vector<sml::Point>&
sml::BaseObject::getPoints() const noexcept
{
    return m_points_with_position;
}