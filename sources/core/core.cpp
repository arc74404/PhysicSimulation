#include "core.hpp"

#include "gui/gui.hpp"

#include "program_state.hpp"

core::Core::Core() noexcept
{
}

void
core::Core::run() noexcept
{
    gui::GUI gui;

    ProgramState& state = ProgramState::getInstance();

    while (state.isAlive())
    {
        state.draw(gui);

        state.update();
    }
}