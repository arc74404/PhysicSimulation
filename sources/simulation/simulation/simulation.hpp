#ifndef SIMULATION_HPP
#define SIMULATION_HPP

#include <unordered_map>

#include "simulation/simulation/field.hpp"

namespace sml
{
using BaseObjectPtr = std::unique_ptr<BaseObject>;

class Simulation
{
public:
    static Simulation& getInstance();

    const std::unordered_map<int, BaseObjectPtr>& getObjectsData()
        const noexcept;

    void update();

private:
    Simulation();

    bool m_pause;

    Field m_field;
};
} // namespace sml

#endif // !SIMULATION_HPP