#include "variable_storage.hpp"

core::VariableStorage::VariableStorage()
{
    m_floats["points_frequency"]        = 3.f;
    m_floats["acceleration_of_gravity"] = 10.f;

    m_floats["elasticity_coefficient"] = 0.5f;

    m_ints["pixels_per_metr"] = 50;
}

core::VariableStorage&
core::VariableStorage::getInstance()
{
    static VariableStorage vs;
    return vs;
}

int
core::VariableStorage::getInt(const std::string& name) const noexcept
{
    int result = 0;

    auto it = m_ints.find(name);

    if (it != m_ints.end())
    {
        result = it->second;
    }
    return result;
}

float
core::VariableStorage::getFloat(const std::string& name) const noexcept
{
    float result = 0.f;

    auto it = m_floats.find(name);

    if (it != m_floats.end())
    {
        result = it->second;
    }
    return result;
}

std::string
core::VariableStorage::getWord(const std::string& name) const noexcept
{
    std::string result = "";

    auto it = m_floats.find(name);

    if (it != m_floats.end())
    {
        result = it->second;
    }
    return result;
}