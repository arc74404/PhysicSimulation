#include "field.hpp"

#include <iostream>

#include "simulation/objects/circle_object.hpp"
#include "simulation/objects/rectangle_object.hpp"

sml::Field::Field()
{
    CircleObject co(100, {100, -1000});
    m_updatable_objects[0] = std::make_unique<CircleObject>(co);
    //////////////////////////////////////////////////
    co.setCentre({300, -100});
    co.setRadius(50);
    m_updatable_objects[1] = std::make_unique<CircleObject>(co);
    //////////////////////////////////////////////////
    co.setRadius(75);
    co.setCentre({300, 200});
    m_updatable_objects[2] = std::make_unique<CircleObject>(co);
    // co.printGlobalBounds();
    //////////////////////////////////////////////////

    RectangleObject r({70, 70}, {100, 1});
    m_updatable_objects[3] = std::make_unique<RectangleObject>(r);

    {
        RectangleObject ro({500, 100}, {0, 500});
        m_const_objects[0] = std::make_unique<RectangleObject>(ro);

        //////////////////////////////////////////////////
        ro.setPosition({1, 1});
        ro.setSize({50, 300});
        m_const_objects[1] = std::make_unique<RectangleObject>(ro);

        // ro.printGlobalBounds();
        //////////////////////////////////////////////////
        RectangleObject ro2({50, 500}, {400, 1});

        m_const_objects[2] = std::make_unique<RectangleObject>(ro2);
    }
}

void
sml::Field::update(float time)
{
    auto ub = m_updatable_objects.begin();
    auto ue = m_updatable_objects.end();

    auto cb = m_const_objects.begin();
    auto ce = m_const_objects.end();

    for (auto i = ub; i != ue; ++i)
    {
        i.operator*().second->updateSpecifications(time);
        auto j = cb;

        bool flag_continue = true;

        for (; j != ce && flag_continue; ++j)
        {
            if (i->second->handleCollision(j->second, true))
                flag_continue = false;
        }
        j = i;
        j++;
        for (; j != ue && flag_continue; ++j)
        {
            if (i->second->handleCollision(j->second)) flag_continue = false;
        }
    }
}

const std::unordered_map<int, sml::BaseObjectPtr>&
sml::Field::getObjectsData(bool is_updatable) const noexcept
{
    if (is_updatable) return m_updatable_objects;
    else return m_const_objects;
}
