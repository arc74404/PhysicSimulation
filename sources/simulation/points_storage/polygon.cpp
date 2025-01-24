#include "polygon.hpp"

#include "simulation/borders/base_equation_border.hpp"

void
sml::Polygon::addBorder(const BaseBorderPtr& b, bool is_final_border,
                        bool allign)
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
    if (is_final_border && allign) allignPoints();
}

void
sml::Polygon::addPoint(const Point& point, bool is_final_point, bool allign)
{
    m_points.emplace_back(point);

    if (is_final_point)
    {
        m_points.emplace_back(m_points[0]);
    }

    if (is_final_point && allign) allignPoints();
}

void
sml::Polygon::copyWithOffset(std::vector<Point>& other_points,
                             Bounds& other_bounds,
                             const sf::Vector2f& offset) const
{
    if (other_points.size() != this->m_points.size())
    {
        other_points.resize(this->m_points.size());
    }
    for (int i = 0; i < other_points.size(); ++i)
    {
        other_points[i] = this->m_points[i] + offset;
    }
    other_bounds.left   = this->m_bounds.left + offset.x;
    other_bounds.right  = this->m_bounds.right + offset.x;
    other_bounds.top    = this->m_bounds.top + offset.y;
    other_bounds.bottom = this->m_bounds.bottom + offset.y;
}

void
sml::Polygon::allignPoints() noexcept
{
    m_bounds.update(m_points);
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
sml::Polygon::clear() noexcept
{
    m_points.clear();
    m_bounds.update(m_points);
}