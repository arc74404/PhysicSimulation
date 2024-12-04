#include "base_object.hpp"

#include <iostream>

sml::BaseObject::BaseObject(FormType form_status) noexcept
    : m_form_status(form_status), can_add_new_border(true)
{
}

void
sml::BaseObject::findMassCenter()
{
}

void
sml::BaseObject::fillPointVector()
{
    if (m_border_vector.empty()) return;

    m_point_vector = m_border_vector[0]->getPoints();

    for (int i = 1; i < m_border_vector.size(); ++i)
    {
        std::vector<Point> points = m_border_vector[i]->getPoints();

        m_point_vector.reserve(m_point_vector.size() + points.size());

        auto it_begin = points.begin();
        auto it_end   = points.end();

        if (points[0] == m_point_vector[m_point_vector.size() - 1])
        {
            it_begin += 1;
        }
        if (points[points.size() - 1] ==
            m_point_vector[m_point_vector.size() - 1])
        {
            it_end -= 1;
        }
        m_point_vector.insert(m_point_vector.end(), it_begin, it_end);
    }

    allign();

    findMassCenter();
}

float
sml::BaseObject::getLeft()
{
    auto comparePoints = [](const Point& a, const Point& b)
    { return a.x < b.x; };

    return std::min_element(m_point_vector.begin(), m_point_vector.end(),
                            comparePoints)
        ->x;
}
float
sml::BaseObject::getTop()
{
    auto comparePoints = [](const Point& a, const Point& b)
    { return a.y > b.y; };

    return std::min_element(m_point_vector.begin(), m_point_vector.end(),
                            comparePoints)
        ->y;
}

float
sml::BaseObject::getRight()
{
    auto comparePoints = [](const Point& a, const Point& b)
    { return a.x > b.x; };

    return std::min_element(m_point_vector.begin(), m_point_vector.end(),
                            comparePoints)
        ->x;
}
float
sml::BaseObject::getBottom()
{
    auto comparePoints = [](const Point& a, const Point& b)
    { return a.y < b.y; };

    return std::min_element(m_point_vector.begin(), m_point_vector.end(),
                            comparePoints)
        ->y;
}

void
sml::BaseObject::allign()
{
    float x_shift = getLeft();
    float y_shift = getBottom();

    for (auto& p : m_point_vector)
    {
        p.x -= x_shift;
        p.y -= y_shift;
    }
}

bool
sml::BaseObject::addBorder(BaseBorderPtr&& b)
{
    if (!can_add_new_border) return false;

    auto size = m_border_vector.size();

    if (size)
    {
        auto& last_el = m_border_vector[size - 1];

        auto con_ways = last_el->getConnectionWays(b);
        if (con_ways[0] == sml::BaseBorder::ConnectionWay::NO_WAY)
        {
            return false;
        }
        if (con_ways.size() == 2)
        {
            if (size == 1)
            {
                can_add_new_border = false;
            }
            else
            {
                return false;
            }
        }
    }
    m_border_vector.emplace_back(std::move(b));
    return true;
}

void
sml::BaseObject::printPoints() noexcept
{
    std::cout << "---------------------------\n";

    for (int i = 0; i < m_point_vector.size(); ++i)
    {
        std::cout << m_point_vector[i].x << " " << m_point_vector[i].y << '\n';
    }

    std::cout << "---------------------------\n";
}
