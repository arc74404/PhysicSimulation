#include "points_storage.hpp"

#include "simulation/borders/base_equation_border.hpp"

void
sml::PointsStorage::addBorder(const BaseBorderPtr& b, bool is_final_border)
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
    }
    if (is_final_border) allignPoints();
}

void
sml::PointsStorage::addPoint(const Point& point, bool is_final_point)
{
    m_points.emplace_back(point);

    if (is_final_point)
    {
        m_points.emplace_back(m_points[0]);
    }

    if (is_final_point) allignPoints();
}

void
sml::PointsStorage::allignPoints() noexcept
{
    float x_shift = m_bounds.left;
    float y_shift = m_bounds.bottom;

    m_bounds.move(-x_shift, -y_shift);

    for (auto& p : m_points)
    {
        p.x -= x_shift;
        p.y -= y_shift;
    }
}

void
sml::PointsStorage::clear() noexcept
{
    m_points.clear();
    m_bounds.update(m_points);
}