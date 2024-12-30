#include "simulation.hpp"

sml::Simulation::Simulation() : m_pause(false)
{
}

sml::Simulation&
sml::Simulation::getInstance()
{
    static Simulation simulation;
    return simulation;
}

void
sml::Simulation::update()
{
    m_field.update();
}

const std::unordered_map<int, sml::BaseObjectPtr>&
sml::Simulation::getObjectsData() const noexcept
{
    return m_field.getObjectsData();
}