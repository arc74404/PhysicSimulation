#ifndef X_CONST_BORDER_HPP
#define X_CONST_BORDER_HPP

#include "base_border.hpp"

namespace sml
{
class XConstBorder : public BaseBorder
{
public:
    template <typename T> XConstBorder(T&& param);

private:
    float x;
};
} // namespace sml

template <typename T>
sml::XConstBorder::XConstBorder(T&& param)
    : BaseBorder(BaseBorder::bType::X_CONST)
{
    x = param;
}

#endif //! X_CONST_BORDER_HPP