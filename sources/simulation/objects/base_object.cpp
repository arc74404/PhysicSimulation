#include "base_object.hpp"

#include <iomanip>
#include <iostream>

sml::BaseObject::BaseObject(FormType form_status) noexcept
    : m_form_type(form_status)
{
}

void
sml::BaseObject::findMassCenter() const
{
}

float
sml::BaseObject::getLeft() const
{
    auto comparePoints = [](const Point& a, const Point& b) noexcept
    { return a.x < b.x; };

    return std::min_element(m_points.begin(), m_points.end(), comparePoints)->x;
}
float
sml::BaseObject::getTop() const
{
    auto comparePoints = [](const Point& a, const Point& b) noexcept
    { return a.y > b.y; };

    return std::min_element(m_points.begin(), m_points.end(), comparePoints)->y;
}

float
sml::BaseObject::getRight() const
{
    auto comparePoints = [](const Point& a, const Point& b) noexcept
    { return a.x > b.x; };

    return std::min_element(m_points.begin(), m_points.end(), comparePoints)->x;
}
float
sml::BaseObject::getBottom() const
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
        p.x -= x_shift;
        p.y -= y_shift;
    }
}

void
sml::BaseObject::addBorder(const BaseBorderPtr& b, bool is_final_border)
{
    auto border_points = b->getPoints();

    m_points.resize(m_points.size() + border_points.size());

    std::copy(border_points.begin(), border_points.end(), m_points.end());

    if (is_final_border)
    {
        allign();
        findMassCenter();
    }
}

void
sml::BaseObject::addPoint(const Point& point, bool is_final_point)
{
    m_points.emplace_back(point);

    if (is_final_point)
    {
        allign();
        findMassCenter();
    }
}

void
sml::BaseObject::update() noexcept
{
}

const std::vector<sml::Point>&
sml::BaseObject::getPoints() const noexcept
{
    return m_points;
}