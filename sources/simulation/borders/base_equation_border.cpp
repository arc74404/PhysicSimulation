#include "base_equation_border.hpp"

sml::BaseEquationBorder::BaseEquationBorder(EquationType e_t,
                                            bool is_cl) noexcept
    : BaseBorder(BaseType::EQUATION), m_equation_type(e_t), is_closed(is_cl)
{
}

sml::BaseEquationBorder::EquationType
sml::BaseEquationBorder::getEquationType()
{
    return m_equation_type;
}
bool
sml::BaseEquationBorder::isClosed()
{
    return is_closed;
}
