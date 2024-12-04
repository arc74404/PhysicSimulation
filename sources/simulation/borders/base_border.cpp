#include "base_border.hpp"

#include "base_equation_border.hpp"

float sml::BaseBorder::m_points_rate = 0.5f;

sml::BaseBorder::BaseBorder(BaseType b_t) noexcept : b_type(b_t)
{
}

constexpr sml::BaseBorder::BaseType
sml::BaseBorder::getBaseType() const noexcept
{
    return b_type;
}

std::vector<sml::BaseBorder::ConnectionWay>
sml::BaseBorder::getConnectionWays(
    std::unique_ptr<sml::BaseBorder>& other_border_ptr) const noexcept
{
    if (other_border_ptr->getBaseType() == BaseType::EQUATION)
    {
        if (static_cast<BaseEquationBorder*>(other_border_ptr.get())
                ->isClosed())
        {
            return {ConnectionWay::NO_WAY};
        }
    }
    std::vector<sml::BaseBorder::ConnectionWay> res;

    if (canConnect(other_border_ptr, ConnectionWay::BEGIN_TO_BEGIN))
        res.emplace_back(ConnectionWay::BEGIN_TO_BEGIN);
    if (canConnect(other_border_ptr, ConnectionWay::BEGIN_TO_END))
        res.emplace_back(ConnectionWay::BEGIN_TO_END);
    if (canConnect(other_border_ptr, ConnectionWay::END_TO_BEGIN))
        res.emplace_back(ConnectionWay::END_TO_BEGIN);
    if (canConnect(other_border_ptr, ConnectionWay::END_TO_END))
        res.emplace_back(ConnectionWay::END_TO_END);

    if (res.size() == 0) res = {ConnectionWay::NO_WAY};

    return res;
}

bool
sml::BaseBorder::canConnect(std::unique_ptr<sml::BaseBorder>& other_border_ptr,
                            ConnectionWay con_way) const noexcept
{

    Point other_connect_point;
    Point this_connect_point;

    switch (con_way)
    {
        case ConnectionWay::END_TO_END:
            other_connect_point = other_border_ptr->getEndPoint();
            this_connect_point  = this->getEndPoint();
            break;
        case ConnectionWay::END_TO_BEGIN:
            other_connect_point = other_border_ptr->getEndPoint();
            this_connect_point  = this->getBeginPoint();
            break;
        case ConnectionWay::BEGIN_TO_END:
            other_connect_point = other_border_ptr->getBeginPoint();
            this_connect_point  = this->getEndPoint();
            break;
        case ConnectionWay::BEGIN_TO_BEGIN:
            other_connect_point = other_border_ptr->getBeginPoint();
            this_connect_point  = this->getBeginPoint();
            break;
        default:
            break;
    }
    return (other_connect_point.x == this_connect_point.x &&
            other_connect_point.y == this_connect_point.y);
}