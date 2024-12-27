#ifndef CIRCLE_BORDER_HPP
#define CIRCLE_BORDER_HPP

#include "base_equation_border.hpp"
#include "def_scope.hpp"
#include "y_limit.hpp"

namespace sml
{
class CircleBorder : public BaseEquationBorder
{
public:
    CircleBorder(float radius, const Point& centre = {0.f, 0.f},
                 float begin = 0, float end = 0) noexcept;

    Point getEndPoint() const noexcept override;

    Point getBeginPoint() const noexcept override;

    std::vector<sml::Point> getPoints() const override;

    // void printData() const override;

private:
    float m_begin_radians;
    float m_end_radians;

    Point m_centre;

    float m_radius;
};
} // namespace sml
#endif // !CIRCLE_BORDER_HPP