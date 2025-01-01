#include "base_object.hpp"

#include <iomanip>
#include <iostream>

#include "core/variable_storage.hpp"
#include "simulation/borders/base_equation_border.hpp"
#include "simulation/simulation/powers.hpp"

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

float
sml::BaseObject::getLeft() const noexcept
{
    auto comparePoints = [](const Point& a, const Point& b) noexcept
    { return a.x < b.x; };

    return std::min_element(m_points.begin(), m_points.end(), comparePoints)->x;
}
float
sml::BaseObject::getTop() const noexcept
{
    auto comparePoints = [](const Point& a, const Point& b) noexcept
    { return a.y > b.y; };

    return std::min_element(m_points.begin(), m_points.end(), comparePoints)->y;
}

float
sml::BaseObject::getRight() const noexcept
{
    auto comparePoints = [](const Point& a, const Point& b) noexcept
    { return a.x > b.x; };

    return std::min_element(m_points.begin(), m_points.end(), comparePoints)->x;
}
float
sml::BaseObject::getBottom() const noexcept
{
    auto comparePoints = [](const Point& a, const Point& b) noexcept
    { return a.y < b.y; };

    return std::min_element(m_points.begin(), m_points.end(), comparePoints)->y;
}

void
sml::BaseObject::allign()
{
    float x_shift = getLeft();
    float y_shift = getBottom();

    for (auto& p : m_points)
    {
        p.x = p.x - x_shift + m_position.x;
        p.y = p.y - y_shift + m_position.y;
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
        allign();
        findMassCenter();
        findMass();
        m_points_with_position = m_points;
    }
}

void
sml::BaseObject::setPosition(const Point& pos)
{
    m_position = pos;

    for (int i = 0; i < m_points_with_position.size(); ++i)
    {
        m_points_with_position[i] = m_points[i] + m_position;
    }
}

void
sml::BaseObject::update(float time) noexcept
{
    auto f = sml::forces::gravity(m_mass);

    int pixels_per_metr =
        core::VariableStorage::getInstance().getInt("pixels_per_metr");

    m_speed.x += f.acceleration.x * time * pixels_per_metr;
    m_speed.y += f.acceleration.y * time * pixels_per_metr;

    m_position.x += m_speed.x * time;
    m_position.y += m_speed.y * time;

    setPosition(m_position);
}

const std::vector<sml::Point>&
sml::BaseObject::getPoints() const noexcept
{
    return m_points_with_position;
}