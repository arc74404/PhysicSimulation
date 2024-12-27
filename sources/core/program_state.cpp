#include "program_state.hpp"

core::ProgramState&
core::ProgramState::getInstance()
{
    static ProgramState program_state;
    return program_state;
}

void
core::ProgramState::draw(gui::GUI& gui)
{
    gui.draw(m_scene);
}