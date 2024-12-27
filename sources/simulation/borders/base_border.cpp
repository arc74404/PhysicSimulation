#include "base_border.hpp"

#include "base_equation_border.hpp"

float sml::BaseBorder::m_points_frequency = 3.f;

float
sml::BaseBorder::getPointsFrequency()
{
    return m_points_frequency;
}

sml::BaseBorder::BaseBorder(BaseType b_t) noexcept : b_type(b_t)
{
}

constexpr sml::BaseBorder::BaseType
sml::BaseBorder::getBaseType() const noexcept
{
    return b_type;
}
