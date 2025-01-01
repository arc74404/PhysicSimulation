#include "simulation.hpp"

sml::Simulation::Simulation() : m_pause(false), m_field()
{
}

sml::Simulation&
sml::Simulation::getInstance()
{
    static Simulation simulation;
    return simulation;
}

void
sml::Simulation::update(float time)
{
    m_field.update(time);
}

const std::unordered_map<int, sml::BaseObjectPtr>&
sml::Simulation::getObjectsData(bool is_updatable) const noexcept
{
    return m_field.getObjectsData(is_updatable);
}