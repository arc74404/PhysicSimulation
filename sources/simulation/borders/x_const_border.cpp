#include "x_const_border.hpp"

#include <iostream>

sml::XisConstBorder::XisConstBorder(float x, YLimit y_l)
    : BaseEquationBorder(EquationType::X_IS_CONST, false), m_x(x),
      m_y_limit(y_l)
{
}

// void
// sml::XisConstBorder::printData() const
// {
//     std::cout << "X: " << m_x << '\n';

//     // std::cout << "X1 - X2 : " << m_function_definition_scope.x1 << " "
//     //           << m_function_definition_scope.x2 << '\n';
// }


sml::Point
sml::XisConstBorder::getEndPoint() const noexcept
{
    return Point(m_x, m_y_limit.y_max);
}

sml::Point
sml::XisConstBorder::getBeginPoint() const noexcept
{
    return Point(m_x, m_y_limit.y_min);
}

std::vector<sml::Point>
sml::XisConstBorder::getPoints() const
{
    return std::vector<sml::Point>({getBeginPoint(), getEndPoint()});
}