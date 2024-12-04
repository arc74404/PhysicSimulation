#ifndef X_CONST_BORDER_HPP
#define X_CONST_BORDER_HPP

#include "base_equation_border.hpp"
#include "y_limit.hpp"

namespace sml
{
class XisConstBorder : public BaseEquationBorder
{
public:
    XisConstBorder(float x, YLimit y_def_scope);

    void printData() const override;

    Point getEndPoint() const noexcept override;

    Point getBeginPoint() const noexcept override;

    std::vector<sml::Point> getPoints() override;

private:
    float getOrdinate(float x) const noexcept override;

    YLimit m_y_limit;

    float m_x;
};
} // namespace sml

#endif //! X_CONST_BORDER_HPP