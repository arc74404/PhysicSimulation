#include "program_state.hpp"

#include <memory>

#include "gui/window.hpp"
#include "simulation/simulation/simulation.hpp"

core::ProgramState::ProgramState() noexcept
{
    m_is_alive = true;

    sml::Simulation& simulation = sml::Simulation::getInstance();
    auto& const_objects_data    = simulation.getObjectsData(false);
    for (auto& obj : const_objects_data)
    {
        m_const_figures[obj.first].updateVertexes(obj.second->getPoints());
    }
}

core::ProgramState&
core::ProgramState::getInstance() noexcept
{
    static ProgramState program_state;
    return program_state;
}

void
core::ProgramState::draw(gui::GUI& gui) noexcept
{
    auto& window = gui::Window::getInstance();
    window.clear();
    gui.draw(m_updatable_figures);
    gui.draw(m_const_figures);
    window.display();
}

void
core::ProgramState::updateGraphics()
{
    sml::Simulation& simulation = sml::Simulation::getInstance();

    auto& upd_objects_data = simulation.getObjectsData(true);

    for (auto& obj : upd_objects_data)
    {
        m_updatable_figures[obj.first].updateVertexes(obj.second->getPoints());
    }
}

void
core::ProgramState::handleEvents()
{
    auto& window = gui::Window::getInstance();

    auto gui_event = window.getEvent();

    if (gui_event == sf::Event::Closed)
    {
        m_is_alive = false;
        window.close();
    }
}

void
core::ProgramState::update()
{
    float time_as_seconds = m_clock.restart().asSeconds();

    handleEvents();
    sml::Simulation::getInstance().update(time_as_seconds);
    updateGraphics();
}

bool
core::ProgramState::isAlive() const noexcept
{
    return m_is_alive;
}
