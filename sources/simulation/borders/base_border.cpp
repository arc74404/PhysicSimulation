#include "base_border.hpp"

#include "base_equation_border.hpp"

sml::BaseBorder::BaseBorder(BaseType b_t) noexcept : b_type(b_t)
{
}

sml::BaseBorder::BaseType
sml::BaseBorder::getBaseType() const noexcept
{
    return b_type;
}
