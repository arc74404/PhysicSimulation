#ifndef PROGRAM_STATE_HPP
#define PROGRAM_STATE_HPP

#include "gui/gui.hpp"

namespace core
{
class ProgramState
{
public:
    static ProgramState& getInstance() noexcept;

    void draw(gui::GUI& gui) noexcept;

    void update();

    bool isAlive() const noexcept;

private:
    ProgramState() noexcept;

    std::vector<gui::GUIObjectPtr> m_gui_objects;

    bool m_is_alive;
};
} // namespace core

#endif // PROGRAM_STATE_HPP