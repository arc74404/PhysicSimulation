#include "circle_border.hpp"

#include <iostream>
#include <numbers>

#include "core/variable_storage.hpp"
#include "util/exta_math_functions.hpp"

sml::CircleBorder::CircleBorder(float radius, const Point& centre, float begin,
                                float end) noexcept
    : BaseEquationBorder(EquationType::CIRCLE,
                         utl::cutBack(begin) == utl::cutBack(end)),
      m_radius(radius)
{
    m_begin_radians = utl::cutBack(begin);
    m_end_radians   = utl::cutBack(end);

    if (m_begin_radians == m_end_radians)
    {
        m_begin_radians = 0;
        m_end_radians   = 2 * std::numbers::pi_v<float>;
    }
}

sml::Point
sml::CircleBorder::getEndPoint() const noexcept
{
    return {m_centre.x + m_radius * std::cos(m_end_radians),
            m_centre.y + m_radius * std::sin(m_end_radians)};
}

sml::Point
sml::CircleBorder::getBeginPoint() const noexcept
{
    return {m_centre.x + m_radius * std::cos(m_begin_radians),
            m_centre.y + m_radius * std::sin(m_begin_radians)};
}

std::vector<sml::Point>
sml::CircleBorder::getPoints() const
{
    std::vector<Point> points;

    float radians   = m_begin_radians;
    float direction = (m_begin_radians < m_end_radians) ? 1.0f : -1.0f;

    float frequency =
        core::VariableStorage::getInstance().getFloat("points_frequency");

    Point point;

    while (radians < m_end_radians * direction)
    {
        point.x = m_centre.x + m_radius * std::cos(radians);
        point.y = m_centre.y + m_radius * std::sin(radians);

        points.emplace_back(point);

        radians += (direction / frequency);
    }
    point.x = m_centre.x + m_radius * std::cos(m_end_radians);
    point.y = m_centre.y + m_radius * std::sin(m_end_radians);
    points.emplace_back(point);

    return points;
}
