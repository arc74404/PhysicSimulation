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
        constexpr YLimit(T yy1, T yy2) noexcept
            : y1(static_cast<float>(yy1)), y2(static_cast<float>(yy2))
        {
        }
        template <typename T>
        constexpr YLimit(std::initializer_list<T> init_list) noexcept
            : y1(static_cast<float>(*init_list.begin())),
              y2(static_cast<float>(*(init_list.end() - 1)))
        {
        }
        float y1;
        float y2;
    };

    XisConstBorder(float x, YLimit y_def_scope);

    void printData() const override;

    Point getEndPoint() const noexcept override;

    Point getBeginPoint() const noexcept override;

private:
    float getOrdinate(float x) const noexcept override;

    YLimit m_y_limit;

    float m_x;
};
} // namespace sml

#endif //! X_CONST_BORDER_HPP