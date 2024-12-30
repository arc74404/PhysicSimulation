#include "field.hpp"

void
sml::Field::update()
{
    for (auto& obj : objects)
        obj.second->update();
}

const std::unordered_map<int, sml::BaseObjectPtr>&
sml::Field::getObjectsData() const noexcept
{
    return objects;
}