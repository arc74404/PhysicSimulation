#include "program_state.hpp"

#include "gui/window.hpp"

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
    gui.draw(m_gui_objects);
}

void
core::ProgramState::update()
{
    auto& window = gui::Window::getInstance();

    auto gui_event = window.getEvent();

    if (gui_event.type == sf::Event::Closed)
    {
        m_is_alive = false;
        window.close();
    }
}

bool
core::ProgramState::isAlive() const noexcept
{
    return m_is_alive;
}
