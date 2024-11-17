#include "linear_border.hpp"

sml::LinearBorder::LinearBorder(DefScope def_scope, float coefficient_K,
                                float coefficient_B)
    : BaseBorder(bType::LINEAR),
      m_function_definition_scope(def_scope.x1, def_scope.x2),
      m_coefficient_K(coefficient_K), m_coefficient_B(coefficient_B)
{
}

void
sml::LinearBorder::printData()
{
    std::cout << "K: " << m_coefficient_K << '\n';

    std::cout << "B: " << m_coefficient_B << '\n';

    std::cout << "X1 - X2 : " << m_function_definition_scope.x1 << " "
              << m_function_definition_scope.x2 << '\n';
}