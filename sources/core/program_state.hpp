#ifndef PROGRAM_STATE_HPP
#define PROGRAM_STATE_HPP

#include <unordered_map>

#include "gui/gui.hpp"

#include "gui/figure.hpp"

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

    std::unordered_map<int, gui::GUIObjectPtr> m_gui_object_ptr_map;

    bool m_is_alive;
};
} // namespace core

#endif // PROGRAM_STATE_HPP