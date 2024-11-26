#include "base_function_border.hpp"

sml::BaseFunctionBorder::DefScope
sml::BaseFunctionBorder::getDefScope() const noexcept
{
    return m_function_definition_scope;
}

sml::BaseFunctionBorder::BaseFunctionBorder(FunctionType f_t,
                                            DefScope def_scope) noexcept
    : BaseBorder(BaseType::FUNCTION), m_function_type(f_t),
      m_function_definition_scope(def_scope)
{
}

sml::Point
sml::BaseFunctionBorder::getEndPoint() const noexcept
{
    return Point({getDefScope().x_max, getOrdinate(getDefScope().x_max)});
}

sml::Point
sml::BaseFunctionBorder::getBeginPoint() const noexcept
{
    return Point({getDefScope().x_min, getOrdinate(getDefScope().x_min)});
}