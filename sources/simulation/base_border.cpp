#include "base_border.hpp"

sml::BaseBorder::BaseBorder(BaseType b_t) noexcept : b_type(b_t)
{
}

constexpr sml::BaseBorder::BaseType
sml::BaseBorder::getBaseType() const noexcept
{
    return b_type;
}

bool
sml::BaseBorder::canConnect(
    std::unique_ptr<sml::BaseBorder>& other_border_ptr) const noexcept
{
    return canConnect(other_border_ptr, ConnectionWay::BEGIN_TO_BEGIN) ||
           canConnect(other_border_ptr, ConnectionWay::BEGIN_TO_END) ||
           canConnect(other_border_ptr, ConnectionWay::END_TO_BEGIN) ||
           canConnect(other_border_ptr, ConnectionWay::END_TO_END);
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