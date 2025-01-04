#include "field.hpp"

#include <iostream>

#include "simulation/objects/circle_object.hpp"
#include "simulation/objects/rectangle_object.hpp"

sml::Field::Field()
{
    CircleObject co(100, {100, 50});
    m_updatable_objects[0] = std::make_unique<CircleObject>(co);
    co.setRadius(50);
    co.setCentre({300, 50});
    m_updatable_objects[1] = std::make_unique<CircleObject>(co);
    co.setRadius(75);
    co.setCentre({600, 50});
    m_updatable_objects[2] = std::make_unique<CircleObject>(co);

    RectangleObject ro({500, 100}, {1, 500});
    m_const_objects[0] = std::make_unique<RectangleObject>(ro);
    ro.setPosition({1, 1});
    ro.setSize({50, 300});
    m_const_objects[1] = std::make_unique<RectangleObject>(ro);
}

void
sml::Field::update(float time)
{
    auto ub = m_updatable_objects.begin();
    auto ue = m_updatable_objects.end();

    auto cb = m_const_objects.begin();
    auto ce = m_const_objects.end();

    for (auto& obj : m_updatable_objects)
    {
        obj.second->update(time);
    }
    // std::cout << "-------------------\n";
    for (auto i = ub; i != ue; ++i)
    {
        auto j = i;
        ++j;
        for (; j != ue; ++j)
        {
            BaseObject::handleCollision(i->second, j->second);
            // std::cout << "U  " << i->first << "  U  " << j->first << '\n';
        }
        j = cb;
        for (auto j = cb; j != ce; ++j)
        {
            BaseObject::handleCollision(i->second, j->second);
            // std::cout << "U  " << i->first << "  C  " << j->first << '\n';
        }
    }
    // std::cout << "-------------------\n";
}

const std::unordered_map<int, sml::BaseObjectPtr>&
sml::Field::getObjectsData(bool is_updatable) const noexcept
{
    if (is_updatable) return m_updatable_objects;
    else return m_const_objects;
}
