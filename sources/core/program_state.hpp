#ifndef PROGRAM_STATE_HPP
#define PROGRAM_STATE_HPP

#include "gui/gui.hpp"
#include "logic/scene.hpp"

namespace core
{
class ProgramState
{
public:
    static ProgramState& getInstance();

    void draw(gui::GUI& gui);

private:
    ProgramState() = default;

    lgc::Scene m_scene;
};
} // namespace core

#endif // PROGRAM_STATE_HPP