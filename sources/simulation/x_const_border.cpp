#include "x_const_border.hpp"

#include <iostream>

sml::XisConstBorder::XisConstBorder(float x, YLimit y_l)
    : BaseEquationBorder(EquationType::XisConst, false), m_x(x), m_y_limit(y_l)
{
}

void
sml::XisConstBorder::printData() const
{
    std::cout << "X: " << m_x << '\n';

    // std::cout << "X1 - X2 : " << m_function_definition_scope.x1 << " "
    //           << m_function_definition_scope.x2 << '\n';
}

float
sml::XisConstBorder::getOrdinate(float x) const noexcept
{
    return m_x;
}

sml::Point
sml::XisConstBorder::getEndPoint() const noexcept
{
    return Point(m_x, m_y_limit.y2);
}

sml::Point
sml::XisConstBorder::getBeginPoint() const noexcept
{
    return Point(m_x, m_y_limit.y1);
}