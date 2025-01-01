#include "field.hpp"

#include "simulation/objects/circle_object.hpp"
#include "simulation/objects/rectangle_object.hpp"

sml::Field::Field()
{
    CircleObject co(100, {200, 200});

    RectangleObject ro({500, 100}, {10, 100});

    m_updatable_objects[0] = std::make_unique<CircleObject>(co);
    m_const_objects[0]     = std::make_unique<RectangleObject>(ro);
}

void
sml::Field::update(float time)
{
    for (auto& obj : m_updatable_objects)
        obj.second->update(time);
}

const std::unordered_map<int, sml::BaseObjectPtr>&
sml::Field::getObjectsData(bool is_updatable) const noexcept
{
    if (is_updatable) return m_updatable_objects;
    else return m_const_objects;
}
