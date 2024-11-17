#ifndef LINEAR_BORDER_HPP
#define LINEAR_BORDER_HPP

#include <SFML/Graphics.hpp>

#include <iostream>

#include "base_border.hpp"

namespace sml
{
class LinearBorder : public BaseBorder
{
public:
    LinearBorder(DefScope def_scope, float coefficient_K = 0,
                 float coefficient_B = 0);

    void printData() override;

private:
    float m_coefficient_K;

    float m_coefficient_B;

    DefScope m_function_definition_scope;
};
} // namespace sml
#endif // !LINEAR_BORDER_HPP