#ifndef PROGRAM_STATE_HPP
#define PROGRAM_STATE_HPP

#include <unordered_map>

#include "gui/figure.hpp"
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

    void updateGraphics();

    void handleEvents();

    std::unordered_map<int, gui::Figure> m_updatable_figures;
    std::unordered_map<int, gui::Figure> m_const_figures;

    bool m_is_alive;
    bool m_is_pause;

    sf::Clock m_clock;
};
} // namespace core

#endif // PROGRAM_STATE_HPP