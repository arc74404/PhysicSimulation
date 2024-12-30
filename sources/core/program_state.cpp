#include "program_state.hpp"

#include <memory>

#include "gui/window.hpp"
#include "simulation/simulation/simulation.hpp"

core::ProgramState::ProgramState() noexcept
{
    m_is_alive = true;
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
    gui.draw(m_gui_object_ptr_map);
}

void
core::ProgramState::update()
{
    sml::Simulation& simulation = sml::Simulation::getInstance();

    auto& objects_data = simulation.getObjectsData();

    for (auto& obj : objects_data)
    {
        std::static_pointer_cast<gui::Figure>(m_gui_object_ptr_map[obj.first])
            ->updateVertexes(obj.second->getPoints());
    }

    auto& window = gui::Window::getInstance();

    auto gui_event = window.getEvent();

    if (gui_event.type == sf::Event::Closed)
    {
        m_is_alive = false;
        window.close();
    }
    // simulation.update();
}

bool
core::ProgramState::isAlive() const noexcept
{
    return m_is_alive;
}
