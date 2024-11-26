#ifndef X_CONST_BORDER_HPP
#define X_CONST_BORDER_HPP

#include "base_equation_border.hpp"

namespace sml
{
class XisConstBorder : public BaseEquationBorder
{
public:
    struct YLimit
    {
        template <typename T>
        constexpr YLimit(T yy_min, T yy_max) noexcept
            : y_min(static_cast<float>(yy_min)),
              y_max(static_cast<float>(yy_max))
        {
            if (y_min > y_max) std::swap(y_min, y_max);
        }
        template <typename T>
        constexpr YLimit(std::initializer_list<T> init_list) noexcept
            : YLimit(*init_list.begin(), *init_list.end())
        {
        }
        float y_min;
        float y_max;
    };

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