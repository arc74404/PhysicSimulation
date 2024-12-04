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

std::vector<sml::BaseBorder::ConnectionWay>
sml::BaseEquationBorder::getConnectionWays(
    std::unique_ptr<BaseBorder>& other_border_ptr) const noexcept
{
    return is_closed ? std::vector<ConnectionWay>({ConnectionWay::NO_WAY})
                     : BaseBorder::getConnectionWays(other_border_ptr);
}

bool
sml::BaseEquationBorder::isClosed()
{
    return is_closed;
}
