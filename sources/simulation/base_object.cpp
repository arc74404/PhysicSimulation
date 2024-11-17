#include "base_object.hpp"

#include <iostream>

// bool
// sml::BaseObject::addBordersImpl(
//     std::initializer_list<BaseBorderPtr> init_list) noexcept
// {
//     m_border_vector.emplace_back(init_list);
//     return true;
// }

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