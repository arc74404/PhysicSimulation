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
    m_points.clear();
    m_points_with_position.clear();
}

sml::Bounds
sml::BaseObject::getLocalBounds() const noexcept
{
    return m_local_bounds;
}

sml::Bounds
sml::BaseObject::getGlobalBounds() const noexcept
{
    return m_global_bounds;
}

void
sml::BaseObject::findLocalBounds() noexcept
{
    m_local_bounds.left =
        std::min_element(m_points.begin(), m_points.end(),
                         [](const Point& a, const Point& b) noexcept
                         { return a.x < b.x; })
            ->x;
    m_local_bounds.right =
        std::min_element(m_points.begin(), m_points.end(),
                         [](const Point& a, const Point& b) noexcept
                         { return a.x > b.x; })
            ->x;
    m_local_bounds.top =
        std::min_element(m_points.begin(), m_points.end(),
                         [](const Point& a, const Point& b) noexcept
                         { return a.y > b.y; })
            ->y;
    m_local_bounds.bottom =
        std::min_element(m_points.begin(), m_points.end(),
                         [](const Point& a, const Point& b) noexcept
                         { return a.y < b.y; })
            ->y;
}

void
sml::BaseObject::findGlobalBounds() noexcept
{
    m_global_bounds.left   = m_local_bounds.left + m_position.x;
    m_global_bounds.right  = m_local_bounds.right + m_position.x;
    m_global_bounds.top    = m_local_bounds.top + m_position.y;
    m_global_bounds.bottom = m_local_bounds.bottom + m_position.y;
}

void
sml::BaseObject::allignPoints()
{
    findLocalBounds();
    float x_shift = getLocalBounds().left;
    float y_shift = getLocalBounds().bottom;

    m_local_bounds.move(-x_shift, -y_shift);

    for (auto& p : m_points)
    {
        p.x -= x_shift;
        p.y -= y_shift;
    }
}

void
sml::BaseObject::createObject()
{
    allignPoints();
    findGlobalBounds();
    findMassCenter();
    findMass();
}

void
sml::BaseObject::addBorder(const BaseBorderPtr& b, bool is_final_border)
{
    auto border_points = b->getPoints();

    m_points.resize(m_points.size() + border_points.size());

    std::copy(border_points.begin(), border_points.end(),
              m_points.end() - border_points.size());

    if (is_final_border)
    {
        if (b->getBaseType() == BaseBorder::BaseType::EQUATION)
        {
            if (!std::static_pointer_cast<BaseEquationBorder>(b)->isClosed())
            {
                m_points.emplace_back(m_points[0]);
            }
        }
        else m_points.emplace_back(m_points[0]);

        createObject();

        m_points_with_position = m_points;
    }
}

void
sml::BaseObject::addPoint(const Point& point, bool is_final_point)
{
    m_points.emplace_back(point);

    if (is_final_point)
    {
        m_points.emplace_back(m_points[0]);

        createObject();
        m_points_with_position = m_points;
    }
}

void
sml::BaseObject::updatePointsPosition()
{
    for (int i = 0; i < m_points_with_position.size(); ++i)
    {
        m_points_with_position[i] = m_points[i] + m_position;
    }
}

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

            float other_speed_module = utl::getLength(other->m_speed);
            float this_speed_module  = utl::getLength(this->m_speed);

            // v1f = ((m1-m2) * v1i + 2 * m2 * v2i) / (m1 + m2)
            if (is_right_const)
            {
                this->m_speed =
                    collision_data->impulse_direction * this_speed_module * other;
            }
            else
            {
                float this_new_speed_module =
                    ((this->m_mass - other->m_mass) * this_speed_module +
                     2 * other->m_mass * other_speed_module) /
                    (this->m_mass + other->m_mass);

                this->m_speed =
                    this_new_speed_module * collision_data->impulse_direction;

                // std::cout << m_speed.x << " " << m_speed.y << '\n';
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