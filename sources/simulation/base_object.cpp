#include "base_object.hpp"

#include <iostream>

bool
sml::BaseObject::addBorder(BaseBorderPtr&& b)
{
    auto size = m_border_vector.size();

    if (size)
    {
        // if (m_border_vector. availableForConnecting())
        // {
        // }
    }
    m_border_vector.emplace_back(std::move(b));
    return true;
}

void
sml::BaseObject::printData() noexcept
{
    std::cout << "---------------------------\n";
    for (std::int8_t i = 0; i < m_border_vector.size(); ++i)
    {
        m_border_vector[i]->printData();
        std::cout << "---------------------------\n";
    }
}