#include "linear_border.hpp"

sml::LinearBorder::LinearBorder(DefScope def_scope, float coefficient_K,
                                float coefficient_B)
    : BaseFunctionBorder(FunctionType::LINEAR, def_scope),
      m_coefficient_K(coefficient_K), m_coefficient_B(coefficient_B)
{
}

void
sml::LinearBorder::printData() const
{
    std::cout << "K: " << m_coefficient_K << '\n';

    std::cout << "B: " << m_coefficient_B << '\n';

    // std::cout << "X1 - X2 : " << m_function_definition_scope.x1 << " "
    //           << m_function_definition_scope.x2 << '\n';
}

float
sml::LinearBorder::getOrdinate(float x) const noexcept
{
    return m_coefficient_K * x + m_coefficient_B;
}

std::vector<sml::Point>
sml::LinearBorder::getPoints()
{
    return std::vector<sml::Point>({getBeginPoint(), getEndPoint()});
}