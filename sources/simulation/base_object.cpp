#include "base_object.hpp"

#include <iostream>

sml::BaseObject::BaseObject(FormType form_status) : m_form_status(form_status)
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

        m_point_vector.reserve(m_point_vector.size() +
                               points.size()); // Выделяем достаточно памяти

        m_point_vector.insert(m_point_vector.end(), points.begin() + 1,
                              points.end());
    }

    findMassCenter();
}

bool
sml::BaseObject::addBorder(BaseBorderPtr&& b)
{
    auto size = m_border_vector.size();

    if (size)
    {
        auto& last_el = m_border_vector[size - 1];
        if (!last_el->canConnect(b))
        {
            return false;
        }
    }
    m_border_vector.emplace_back(std::move(b));
    return true;
}

void
sml::BaseObject::printData() noexcept
{
    std::cout << "---------------------------\n";
    std::cout << "position: " << m_position.x << " " << m_position.y << '\n\n';

    for (int i = 0; i < m_border_vector.size(); ++i)
    {
        m_border_vector[i]->printData();
        std::cout << "---\n";
    }

    std::cout << "---------------------------\n";
}