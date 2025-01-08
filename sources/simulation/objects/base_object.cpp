#include "base_object.hpp"

#include <iomanip>
#include <iostream>

#include "core/variable_storage.hpp"
#include "simulation/borders/base_equation_border.hpp"
#include "simulation/simulation/powers.hpp"
#include "util/collision_functions.hpp"
#include "util/extra_math_functions.hpp"

sml::BaseObject::BaseObject(FormType form_status) noexcept
    : m_form_type(form_status), m_speed(0, 0)
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
}

void
sml::BaseObject::deleteAllPoints() noexcept
{
    m_points.clear();
    m_points_with_position.clear();
}

sml::Bounds
sml::BaseObject::getBounds() const noexcept
{
    return m_bounds;
}

void
sml::BaseObject::findBounds()
{
    m_bounds.left = std::min_element(m_points.begin(), m_points.end(),
                                     [](const Point& a, const Point& b) noexcept
                                     { return a.x < b.x; })
                        ->x;
    m_bounds.right =
        std::max_element(m_points.begin(), m_points.end(),
                         [](const Point& a, const Point& b) noexcept
                         { return a.x > b.x; })
            ->x;
    m_bounds.top = std::max_element(m_points.begin(), m_points.end(),
                                    [](const Point& a, const Point& b) noexcept
                                    { return a.y > b.y; })
                       ->y;
    m_bounds.bottom =
        std::min_element(m_points.begin(), m_points.end(),
                         [](const Point& a, const Point& b) noexcept
                         { return a.y < b.y; })
            ->y;
}

void
sml::BaseObject::allign()
{
    float x_shift = getBounds().left;
    float y_shift = getBounds().bottom;

    for (auto& p : m_points)
    {
        p.x -= x_shift;
        p.y -= y_shift;
    }
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

        findBounds();
        allign();
        findMassCenter();
        findMass();

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

        findBounds();
        allign();
        findMassCenter();
        findMass();
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

    m_bounds.left += vec.x;
    m_bounds.right += vec.x;
    m_bounds.top += vec.y;
    m_bounds.bottom += vec.y;

    updatePointsPosition();
}

void
sml::BaseObject::setPosition(const Point& pos)
{
    sf::Vector2f move_vec = pos - m_position;
    move(move_vec);
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

bool
sml::BaseObject::isBoundsIntersect(const sml::BaseObjectPtr other)
{
    sf::IntRect rect1;
    rect1.top    = this->m_bounds.top;
    rect1.left   = this->m_bounds.left;
    rect1.width  = this->m_bounds.right - this->m_bounds.left;
    rect1.height = this->m_bounds.top - this->m_bounds.bottom;

    sf::IntRect rect2;
    rect2.top    = other->m_bounds.top;
    rect2.left   = other->m_bounds.left;
    rect2.width  = other->m_bounds.right - other->m_bounds.left;
    rect2.height = other->m_bounds.top - other->m_bounds.bottom;

    return rect1.intersects(rect2);
}

void
sml::BaseObject::handleCollision(std::shared_ptr<BaseObject> other,
                                 bool is_right_const) noexcept
{
    auto allign_vector =
        utl::allignVector(this->m_points_with_position, this->m_speed,
                          other->m_points_with_position);

    if (allign_vector.x != 0 || allign_vector.y != 0)
    {
        move(allign_vector);
    }
}

const std::vector<sml::Point>&
sml::BaseObject::getPoints() const noexcept
{
    return m_points_with_position;
}