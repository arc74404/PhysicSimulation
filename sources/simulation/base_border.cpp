#include "base_border.hpp"

sml::BaseBorder::BaseBorder(bType bt, DefScope def_scope) noexcept
    : b_type(bt), m_function_definition_scope(def_scope)
{
}

sml::BaseBorder::DefScope
sml::BaseBorder::getDefScope() const noexcept
{
    return m_function_definition_scope;
}

constexpr sml::BaseBorder::bType
sml::BaseBorder::getType() const noexcept
{
    return b_type;
}

sml::Point
sml::BaseBorder::getEndPoint() const
{
    return Point({getDefScope().x2, getOrdinate(getDefScope().x2)});
}

sml::Point
sml::BaseBorder::getBeginPoint() const
{
    return Point({getDefScope().x1, getOrdinate(getDefScope().x1)});
}

bool
sml::BaseBorder::canConnect(std::unique_ptr<sml::BaseBorder>& other_border_ptr,
                            ConnectionWay con_way) const
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