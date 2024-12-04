#include "circle_border.hpp"

#include "util/exta_math_functions.hpp"

sml::CircleBorder::CircleBorder(float radius, const Point& centre, float begin,
                                float end) noexcept
    : BaseEquationBorder(EquationType::CIRCLE,
                         utl::cutBack(begin) == utl::cutBack(end))
{
    m_begin = utl::cutBack(begin);
    m_end   = utl::cutBack(end);
}

sml::Point
sml::BaseBorder::getEndPoint() const noexcept
{
}

sml::Point
sml::BaseBorder::getBeginPoint() const noexcept
{
}

std::vector<sml::Point>
getPoints()
{
}