#ifndef LINEAR_BORDER_HPP
#define LINEAR_BORDER_HPP

#include <SFML/Graphics.hpp>

#include <iostream>

#include "base_function_border.hpp"

namespace sml
{

using BaseBorderPtr = std::unique_ptr<sml::BaseBorder>;

class LinearBorder : public BaseFunctionBorder
{
public:
    LinearBorder(DefScope def_scope, float coefficient_K = 0,
                 float coefficient_B = 0);

    std::vector<Point> getPoints() const override;

private:
    virtual float getOrdinate(float x) const noexcept override;

    float m_coefficient_K;

    float m_coefficient_B;
};
} // namespace sml
#endif // !LINEAR_BORDER_HPP